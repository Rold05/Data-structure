#include <stdio.h>
#include <stdlib.h>

#define QUEUESIZE 5

int isEmpty(int count) { return count == 0; }
int isFull (int count) { return count == QUEUESIZE; }

void draw_logical_view(const int q[], int front, int count) {
    printf("Logical view (front -> rear): ");
    if (count == 0) { puts("[empty]"); return; }
    for (int i = 0; i < count; i++) {
        int idx = (front + i) % QUEUESIZE;
        printf("%d", q[idx]);
        if (i < count - 1) printf(" <- ");
    }
    puts("");
}

void draw_buffer_view(const int q[], int front, int rear, int count) {
    printf("Idx:   ");
    for (int i = 0; i < QUEUESIZE; i++) printf("%3d ", i);
    puts("");

    printf("Data:  ");
    for (int i = 0; i < QUEUESIZE; i++) {
        int used = 0;
        for (int k = 0; k < count; k++) {
            if (((front + k) % QUEUESIZE) == i) { used = 1; break; }
        }
        if (used) printf("%3d ", q[i]);
        else       printf("  _ ");
    }
    puts("");

    printf("Mark:  ");
    for (int i = 0; i < QUEUESIZE; i++) {
        int markF = (count > 0 && i == front);
        int markR = (i == rear);
        if (markF && markR)
            printf(" FR ");
        else if (markF)
            printf("  F ");
        else if (markR)
            printf("  R ");
        else
            printf("    ");
    }
    puts("\n");
}

void show_state(const char *action, int value, const int q[], int front, int rear, int count) {
    if (action && *action) {
        if (value == 2147483647) {
            printf("Action: %s\n", action);
        } else {
            printf("Action: %s %d\n", action, value);
        }
    }
    printf("front=%d, rear=%d, size=%d/%d\n", front, rear, count, QUEUESIZE);
    draw_logical_view(q, front, count);
    draw_buffer_view(q, front, rear, count);
    puts("------------------------------------------------------------");
}

int enqueue(int q[], int *rear, int *count, int value) {
    if (isFull(*count)) return 0;
    q[*rear] = value;
    *rear = (*rear + 1) % QUEUESIZE;
    (*count)++;
    return 1;
}

int dequeue(int q[], int *front, int *count, int *out) {
    if (isEmpty(*count)) return 0;
    *out = q[*front];
    *front = (*front + 1) % QUEUESIZE;
    (*count)--;
    return 1;
}

int main(void) {
    int queue[QUEUESIZE] = {0};
    int front = 0, rear = 0, numCurrentElements = 0;

    puts("Queue visual demo (capacity=5).");
    show_state("Start", 2147483647, queue, front, rear, numCurrentElements);

    while (1) {
        int decide;
        printf("Choose: 1) Enqueue  2) Dequeue  3) Exit\n> ");
        if (scanf("%d", &decide) != 1) {
            int c; while ((c = getchar()) != '\n' && c != EOF) {}
            puts("Invalid input.");
            continue;
        }

        if (decide == 1) {
            int v;
            printf("Enter integer to enqueue: ");
            if (scanf("%d", &v) != 1) {
                int c; while ((c = getchar()) != '\n' && c != EOF) {}
                puts("Invalid number.");
                continue;
            }
            if (enqueue(queue, &rear, &numCurrentElements, v)) {
                show_state("Enqueued", v, queue, front, rear, numCurrentElements);
            } else {
                show_state("Enqueue failed (full). Tried", v, queue, front, rear, numCurrentElements);
            }
        } else if (decide == 2) {
            int out;
            if (dequeue(queue, &front, &numCurrentElements, &out)) {
                show_state("Dequeued", out, queue, front, rear, numCurrentElements);
            } else {
                show_state("Dequeue failed (empty).", 2147483647, queue, front, rear, numCurrentElements);
            }
        } else if (decide == 3) {
            puts("Exiting...");
            break;
        } else {
            puts("Invalid option.");
        }
    }

    return 0;
}
