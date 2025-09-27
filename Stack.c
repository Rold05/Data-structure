#include <stdio.h>

#define CAP 100000

static int isEmptyP(int top) { return top == -1; }
static int isFullP(int top, int cap) { return top == cap - 1; }

static int match(char o, char c) {
    return (o=='(' && c==')') || (o=='[' && c==']') || (o=='{' && c=='}');
}

int main(void) {
    static char s[CAP + 5];
    if (!fgets(s, sizeof s, stdin)) return 0;

    typedef struct { char ch; int idx; } Node;
    static Node st[CAP];
    int top = -1;

    for (int i = 0; s[i] && s[i] != '\n'; ++i) {
        char c = s[i];
        if (c=='(' || c=='[' || c=='{') {
            if (isFullP(top, CAP)) {
                printf("ERROR %d\n", i);
                return 0;
            }
            st[++top] = (Node){ c, i };
        } else if (c==')' || c==']' || c=='}') {
            if (isEmptyP(top)) {
                printf("ERROR %d\n", i);
                return 0;
            }
            if (!match(st[top].ch, c)) {
                printf("ERROR %d\n", i);
                return 0;
            }
            --top;
        }
    }

    if (!isEmptyP(top)) {
        printf("ERROR %d\n", st[0].idx);
        return 0;
    }

    printf("OK\n");
    return 0;
}

