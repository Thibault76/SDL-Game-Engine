#pragma once

#include "../core.h"

#define CeosLinkedListInsert(list, data) __CeosLinkedListInsert(list, (void *)data)
#define CeosLinkedListInsertLast(list, data) __CeosLinkedListInsertLast(list, (void *)data)

/* STRUCTURES */

typedef struct CeosLinkedListNode {
    struct CeosLinkedListNode *prev;
    struct CeosLinkedListNode *next;
    void *data;
} CeosLinkedListNode;

typedef struct CeosLinkedList{
    CeosLinkedListNode *first;
    CeosLinkedListNode *last;
    int size;
} CeosLinkedList;

/* Functions */

CeosLinkedList *CeosLinkedListCreate(void);
CeosLinkedList *CeosLinkedListFree(CeosLinkedList *list);
Bool CeosLinkedListIsEmpty(CeosLinkedList *list);
void __CeosLinkedListInsert(CeosLinkedList *list, void *data);
void CeosLinkedListDelete(CeosLinkedList *list);
void __CeosLinkedListInsertLast(CeosLinkedList *list, void *data);
void CeosLinkedListDeleteLast(CeosLinkedList *list);
CeosLinkedListNode *CeosLinkedListCreateNode(void);
CeosLinkedListNode *CeosLinkedListFreeNode(CeosLinkedListNode *node);
void CeosLinkedListDisplayForwardInt(CeosLinkedList *list);
void CeosLinkedListDisplayBackwardInt(CeosLinkedList *list);