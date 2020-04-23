#ifndef LAB5_DBLLINKEDLIST_H
#define LAB5_DBLLINKEDLIST_H
#include <stddef.h>

typedef struct _Node {
    void *value;
    struct _Node *next;
    struct _Node *prev;
} Node;

typedef struct _DblLinkedList {
    size_t size;
    Node *head;
    Node *tail;
} DblLinkedList;

DblLinkedList* createDblLinkedList();
void deleteDblLinkedList(DblLinkedList **list);
void pushFront(DblLinkedList *list, void *data);
void pushBack(DblLinkedList *list, void *value);
void* popFront(DblLinkedList *list);
void* popBack(DblLinkedList *list);

#endif //LAB5_DBLLINKEDLIST_H
