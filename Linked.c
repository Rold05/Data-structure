#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    struct node* next;
} Node;

Node* head = NULL;

Node* createNode(int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode != NULL) {
        newNode->data = value;
        newNode->next = NULL;
    }
    return newNode;
}

void displayList() {
    if (head == NULL) {
        printf("The list is EMPTY!\n");
    } else {
        Node* aux = head;
        printf("List: ");
        while (aux != NULL) {
            printf("%d -> ", aux->data);
            aux = aux->next;
        }
        printf("NULL\n");
    }
}

void insertAtBeginning(int value) {
    Node* newNode = createNode(value);
    if (newNode != NULL) {
        newNode->next = head;
        head = newNode;
    }
}

void insertAtPosition(int value, int position) {
    if (position <= 1 || head == NULL) {
        insertAtBeginning(value);
        return;
    }
    Node* newNode = createNode(value);
    if (newNode == NULL) return;
    Node* aux = head;
    int i;
    for (i = 1; i < position - 1 && aux->next != NULL; i++) {
        aux = aux->next;
    }
    newNode->next = aux->next;
    aux->next = newNode;
}

void insertAtEnd(int value) {
    Node* newNode = createNode(value);
    if (newNode == NULL) return;
    if (head == NULL) {
        head = newNode;
    } else {
        Node* aux = head;
        while (aux->next != NULL) {
            aux = aux->next;
        }
        aux->next = newNode;
    }
}

void deleteAtBeginning() {
    if (head == NULL) {
        printf("List is empty. Nothing to delete.\n");
        return;
    }
    Node* temp = head;
    head = head->next;
    free(temp);
}

void deleteAtEnd() {
    if (head == NULL) {
        printf("List is empty. Nothing to delete.\n");
        return;
    }
    if (head->next == NULL) {
        free(head);
        head = NULL;
        return;
    }
    Node* aux = head;
    while (aux->next->next != NULL) {
        aux = aux->next;
    }
    free(aux->next);
    aux->next = NULL;
}

void deleteAtPosition(int position) {
    if (head == NULL) {
        printf("List is empty. Nothing to delete.\n");
        return;
    }
    if (position <= 1) {
        deleteAtBeginning();
        return;
    }
    Node* aux = head;
    int i;
    for (i = 1; i < position - 1 && aux->next != NULL; i++) {
        aux = aux->next;
    }
    if (aux->next == NULL) {
        printf("Position out of range.\n");
        return;
    }
    Node* temp = aux->next;
    aux->next = temp->next;
    free(temp);
}

int main() {
    insertAtEnd(10);
    insertAtEnd(20);
    insertAtEnd(30);
    displayList();

    insertAtBeginning(5);
    displayList();

    insertAtPosition(15, 3);
    displayList();

    deleteAtBeginning();
    displayList();

    deleteAtEnd();
    displayList();

    deleteAtPosition(2);
    displayList();

    return 0;
}
