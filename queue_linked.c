
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

typedef struct {
    Node *front;
    Node *rear;
    size_t size;
} Queue;


void queue_init(Queue *q) {
    q->front = q->rear = NULL;
    q->size = 0;
}

int queue_is_empty(const Queue *q) {
    return q->size == 0;
}

int queue_enqueue(Queue *q, int value) {
    Node *n = (Node*)malloc(sizeof(Node));
    if (!n) return 0;
    n->data = value;
    n->next = NULL;
    if (q->rear) {
        q->rear->next = n;    
    } else {
        q->front = n;         
    }
    q->rear = n;              
    q->size++;
    return 1;
}

int queue_dequeue(Queue *q, int *out_value) {
    if (queue_is_empty(q)) return 0;
    Node *aux = q->front;        
    if (out_value) *out_value = aux->data;
    q->front = aux->next;        
    if (!q->front) q->rear = NULL; 
    free(aux);
    q->size--;
    return 1;
}

int queue_peek(const Queue *q, int *out_value) {
    if (queue_is_empty(q)) return 0;
    if (out_value) *out_value = q->front->data;
    return 1;
}

void queue_clear(Queue *q) {
    Node *cur = q->front;
    while (cur) {
        Node *next = cur->next;
        free(cur);
        cur = next;
    }
    q->front = q->rear = NULL;
    q->size = 0;
}

void queue_show(const Queue *q) {
    const Node *aux = q->front;
    printf("[front] ");
    while (aux) {
        printf("%d ", aux->data);
        aux = aux->next;
    }
    printf("[rear]  (size=%zu)\n", q->size);
}

static void flush_stdin(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

int main(void) {
    Queue q;
    queue_init(&q);
    int running = 1;

    while (running) {
        printf("\nQueue (linked list) menu\n");
        printf("1) Enqueue\n");
        printf("2) Dequeue\n");
        printf("3) Peek front\n");
        printf("4) Show queue\n");
        printf("5) Clear queue\n");
        printf("0) Exit\n");
        printf("Select: ");

        int opt;
        if (scanf("%d", &opt) != 1) {
            puts("Invalid input."); flush_stdin(); continue;
            }
        flush_stdin();

        switch (opt) {
            case 1: {
                int x;
                printf("Value to enqueue: ");
                if (scanf("%d", &x) != 1) {
                    puts("Invalid number."); flush_stdin(); break; 
                }
                flush_stdin();
                
                if (queue_enqueue(&q, x)) puts("Enqueued.");
                else puts("Allocation failed.");
            } break;
            case 2: {
                int v;
                if (queue_dequeue(&q, &v)) printf("Dequeued: %d\n", v);
                else puts("Queue is empty.");
            } break;
            case 3: {
                int v;
                if (queue_peek(&q, &v)) printf("Front: %d\n", v);
                else puts("Queue is empty.");
            } break;
            case 4:
                queue_show(&q);
                break;
            case 5:
                queue_clear(&q);
                puts("Queue cleared.");
                break;
            case 0:
                running = 0;
                break;
            default:
                puts("Unknown option.");
        }
    }

    queue_clear(&q);
    return 0;
}
