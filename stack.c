#include <stdio.h>
#define MAX 10

int stack[MAX], top = -1;

void push(int val) {
    if (top < MAX - 1)
        stack[++top] = val;
}

int pop() {
    if (top >= 0)
        return stack[top--];
    return -1;
}

int main() {
    push(2);
    push(4);
    pop();
    push(6);
    push(8);
    pop();
    pop();
    return 0;
}
