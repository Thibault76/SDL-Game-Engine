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
    struct CeosLinkedList *pool;
    int size;
    int step;
    Bool isPreprossed;
} CeosLinkedList;

/* Functions */

CeosLinkedList *CeosLinkedListCreate(Bool isPreprossed, int poolSize, int step);
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
void CeosLinkedListInitPool(CeosLinkedList *list, int size);
int CeosLinkedListSize(CeosLinkedList *list);
void CeosLinkedListDisplayPoolSize(CeosLinkedList *list);
CeosLinkedListNode *CeosLinkedListReturnFirstNode(CeosLinkedList *list);
CeosLinkedListNode *CeosLinkedListReturnLastNode(CeosLinkedList *list);