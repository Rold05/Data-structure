#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct {
    Node* head;
    Node* tail;
    size_t size;
} CList;

void clist_init(CList* L) { L->head = L->tail = NULL; L->size = 0; }
bool clist_is_empty(const CList* L) { return L->size == 0; }
size_t clist_size(const CList* L) { return L->size; }

static Node* make_node(int x) {
    Node* n = (Node*)malloc(sizeof(Node));
    n->data = x; n->next = NULL; return n;
}

void clist_add_front(CList* L, int x) {
    Node* n = make_node(x);
    if (clist_is_empty(L)) { L->head = L->tail = n; n->next = n; }
    else { n->next = L->head; L->tail->next = n; L->head = n; }
    L->size++;
}

void clist_add_end(CList* L, int x) {
    Node* n = make_node(x);
    if (clist_is_empty(L)) { L->head = L->tail = n; n->next = n; }
    else { n->next = L->head; L->tail->next = n; L->tail = n; }
    L->size++;
}

void clist_add_at(CList* L, int x, size_t pos) {
    if (pos <= 1) { clist_add_front(L, x); return; }
    if (pos > L->size) { clist_add_end(L, x); return; }
    Node* n = make_node(x); Node* cur = L->head;
    for (size_t i = 1; i < pos - 1; i++) cur = cur->next;
    n->next = cur->next; cur->next = n; L->size++;
}

bool clist_remove_front(CList* L, int* out) {
    if (clist_is_empty(L)) return false;
    Node* del = L->head; if (out) *out = del->data;
    if (L->size == 1) { L->head = L->tail = NULL; }
    else { L->head = del->next; L->tail->next = L->head; }
    free(del); L->size--; return true;
}

bool clist_remove_end(CList* L, int* out) {
    if (clist_is_empty(L)) return false;
    if (L->size == 1) return clist_remove_front(L, out);
    Node* prev = L->head; while (prev->next != L->tail) prev = prev->next;
    Node* del = L->tail; if (out) *out = del->data;
    prev->next = L->head; L->tail = prev; free(del); L->size--; return true;
}

bool clist_remove_at(CList* L, size_t pos, int* out) {
    if (clist_is_empty(L)) return false;
    if (pos <= 1) return clist_remove_front(L, out);
    if (pos >= L->size) return clist_remove_end(L, out);
    Node* prev = L->head; for (size_t i = 1; i < pos - 1; i++) prev = prev->next;
    Node* del = prev->next; if (out) *out = del->data;
    prev->next = del->next; free(del); L->size--; return true;
}

int clist_search(const CList* L, int key) {
    if (clist_is_empty(L)) return -1;
    Node* cur = L->head;
    for (size_t i = 1; i <= L->size; i++) {
        if (cur->data == key) return (int)i;
        cur = cur->next;
    }
    return -1;
}

void clist_traverse(const CList* L, void (*visit)(int)) {
    if (clist_is_empty(L)) return;
    Node* cur = L->head;
    for (size_t i = 0; i < L->size; i++) { visit(cur->data); cur = cur->next; }
}

void clist_clear(CList* L) { while (!clist_is_empty(L)) { int x; clist_remove_front(L, &x); } }
bool clist_get_head(const CList* L, int* out) { if (clist_is_empty(L)) return false; *out = L->head->data; return true; }
bool clist_get_tail(const CList* L, int* out) { if (clist_is_empty(L)) return false; *out = L->tail->data; return true; }

void clist_display(const CList* L) {
    if (clist_is_empty(L)) { printf("List: [ ]\n"); return; }
    Node* cur = L->head;
    printf("List: [ ");
    for (size_t i = 0; i < L->size; i++) {
        printf("%d", cur->data); if (i + 1 < L->size) printf(" -> ");
        cur = cur->next;
    }
    printf(" ]\n");
}

static void print_val(int x) { printf("%d ", x); }

int main() {
    CList L; clist_init(&L);
    int choice, val, pos, out;
    do {
        printf("\n1.AddFront 2.AddEnd 3.AddAt 4.RemFront 5.RemEnd 6.RemAt\n");
        printf("7.Search 8.Traverse 9.Size 10.IsEmpty 11.Clear 12.Display\n");
        printf("13.GetHead 14.GetTail 0.Exit\nChoice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1: printf("Value: "); scanf("%d", &val); clist_add_front(&L, val); break;
            case 2: printf("Value: "); scanf("%d", &val); clist_add_end(&L, val); break;
            case 3: printf("Value: "); scanf("%d", &val); printf("Pos: "); scanf("%d", &pos); clist_add_at(&L, val, pos); break;
            case 4: if (clist_remove_front(&L, &out)) printf("Removed: %d\n", out); break;
            case 5: if (clist_remove_end(&L, &out)) printf("Removed: %d\n", out); break;
            case 6: printf("Pos: "); scanf("%d", &pos); if (clist_remove_at(&L, pos, &out)) printf("Removed: %d\n", out); break;
            case 7: printf("Key: "); scanf("%d", &val); pos = clist_search(&L, val); printf("Pos: %d\n", pos); break;
            case 8: clist_traverse(&L, print_val); printf("\n"); break;
            case 9: printf("Size: %zu\n", clist_size(&L)); break;
            case 10: printf("Empty: %s\n", clist_is_empty(&L) ? "Yes" : "No"); break;
            case 11: clist_clear(&L); break;
            case 12: clist_display(&L); break;
            case 13: if (clist_get_head(&L, &out)) printf("Head: %d\n", out); break;
            case 14: if (clist_get_tail(&L, &out)) printf("Tail: %d\n", out); break;
        }
    } while (choice != 0);
    clist_clear(&L);
    return 0;
}
