# Data-structure
#include <stdio.h>
#include <stdlib.h>

#define QUEUESIZE 5

// Use the same names you started with, but at file scope
int queue[QUEUESIZE];
int front = 0;                
int rear = 0;                  
int numCurrentElements = 0;    

int isEmpty(void) {
    return numCurrentElements == 0;
}

int isFull(void) {
    return numCurrentElements == QUEUESIZE;
}

void display(void) {
    if (isEmpty()) {
        printf("Queue is empty.\n");
        return;
    }
    printf("Queue contents: ");
    for (int i = 0; i < numCurrentElements; i++) {
        int idx = (front + i) % QUEUESIZE;
        printf("%d ", queue[idx]);
    }
    printf("\n");
}

void enqueue(int value) {
    if (isFull()) {
        printf("Queue is full! Cannot enqueue %d.\n", value);
        return;
    }
    queue[rear] = value;
    rear = (rear + 1) % QUEUESIZE;
    numCurrentElements++;
    printf("Enqueued: %d\n", value);
}

int dequeue(void) {
    if (isEmpty()) {
        printf("Queue is empty! Cannot dequeue.\n");
        return -1; // sentinel for "no value"
    }
    int value = queue[front];
    front = (front + 1) % QUEUESIZE;
    numCurrentElements--;
    return value;
}

int main(void) {
    int decide;
    int value;

    while (1) {
        printf("\nDo you want to enqueue or dequeue?\n");
        printf("1) Enqueue\n");
        printf("2) Dequeue\n");
        printf("3) Exit\n");
        printf("Your choice: ");

        if (scanf("%d", &decide) != 1) {
            // Clear invalid input
            int c;
            while ((c = getchar()) != '\n' && c != EOF) {}
            printf("Invalid input. Try again.\n");
            continue;
        }

        if (decide == 1) {
            printf("Enter an integer to enqueue: ");
            if (scanf("%d", &value) != 1) {
                int c;
                while ((c = getchar()) != '\n' && c != EOF) {}
                printf("Invalid number.\n");
                continue;
            }
            enqueue(value);
            display();
        } else if (decide == 2) {
            value = dequeue();
            if (value != -1) {
                printf("Dequeued: %d\n", value);
            }
            display();
        } else if (decide == 3) {
            printf("Exiting...\n");
            break;
        } else {
            printf("Invalid choice. Try again.\n");
        }
    }

    return 0;
}
