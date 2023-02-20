#include <stdio.h>

typedef struct _node {
    void* data;
    struct _node* next;
} Node;

typedef struct _linked_list {
    Node* head;
    Node* tail;
    Node* current;
} LinkedList;

void initiallize_list(LinkedList* list)
{
    list->head = NULL;
    list->tail = NULL;
    list->current = NULL;
}

void add_head(LinkedList* list, void* data)
{
    Node* node = (Node*) malloc(sizeof(Node));
    node->data = data;
    if (list->head == NULL) {
        list->tail = node;
        node->next = NULL;
    } else {
        node->next = list->head;
    }
    list->head = node;  // Regardless, the list's head is assigned to the node;
}
