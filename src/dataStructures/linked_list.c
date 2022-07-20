#include "engine/dataStructure/linked_list.h"

#include <stdio.h>
#include <stdlib.h>

/*--------------------------------------------*/

CeosLinkedList *CeosLinkedListCreate(void){
    CeosLinkedList *list;
    list = malloc(sizeof(CeosLinkedList));
    MALLOC_CHECK(list)

    list->first = NULL;
    list->last = NULL;
    list->size = 0;

    return list;
}

/*--------------------------------------------*/

CeosLinkedList *CeosLinkedListFree(CeosLinkedList *list){
    free(list);
    return NULL;
}

/*--------------------------------------------*/

Bool CeosLinkedListIsEmpty(CeosLinkedList *list){
    if(list->first == NULL && list->last == NULL){
        return true;
    }

    return false;
}

/*--------------------------------------------*/

void __CeosLinkedListInsert(CeosLinkedList *list, void *data){
    CeosLinkedListNode *node = CeosLinkedListCreateNode();
    node->data = data;

    if(CeosLinkedListIsEmpty(list)){
        list->first = node;
        list->last = node;
    } else {
        node->next = list->first;
        list->first->prev = node;
        list->first = node;
    }
    list->size++;
}

/*--------------------------------------------*/

void CeosLinkedListDelete(CeosLinkedList *list){
    if(CeosLinkedListIsEmpty(list)){
        return;
    }

    CeosLinkedListNode *node = list->first;

    if(list->size == 1){
        list->first = NULL;
        list->last = NULL;
    } else {
        list->first = list->first->next;
        list->first->prev = NULL;
    }

    list->size--;

    node = CeosLinkedListFreeNode(node);
}

/*--------------------------------------------*/

CeosLinkedListNode *CeosLinkedListCreateNode(void){
    CeosLinkedListNode *node = malloc(sizeof(CeosLinkedListNode));
    MALLOC_CHECK(node)

    node->data = NULL;
    node->next = NULL;
    node->prev = NULL;

    return node;
}

/*--------------------------------------------*/

CeosLinkedListNode *CeosLinkedListFreeNode(CeosLinkedListNode *node){
    free(node);
    return NULL;
}

/*--------------------------------------------*/

void CeosLinkedListDisplayForwardInt(CeosLinkedList *list){
    CeosLinkedListNode *node = list->first;
    printf("\n-----------------------------------------------------\n");
    if(CeosLinkedListIsEmpty(list))
        printf("EMPTY");

    while(node != NULL){
        printf("[%d], ", (int*)node->data);
        node = node->next;
    }
    printf("\n-----------------------------------------------------\n");
}

/*--------------------------------------------*/

void CeosLinkedListDisplayBackwardInt(CeosLinkedList *list){
    CeosLinkedListNode *node = list->last;
    printf("\n-----------------------------------------------------\n");
    if(CeosLinkedListIsEmpty(list))
        printf("EMPTY");

    while(node != NULL){
        printf("[%d], ", (int*)node->data);
        node = node->prev;
    }
    printf("\n-----------------------------------------------------\n");
}

/*--------------------------------------------*/

void __CeosLinkedListInsertLast(CeosLinkedList *list, void *data){
    CeosLinkedListNode *node = CeosLinkedListCreateNode();
    node->data = data;

    if(CeosLinkedListIsEmpty(list)){
        list->first = node;
        list->last = node;
    } else {
        node->prev = list->last;
        list->last->next = node;
        list->last = node;
    }
    list->size++;
}

/*--------------------------------------------*/

void CeosLinkedListDeleteLast(CeosLinkedList *list){
    if(CeosLinkedListIsEmpty(list)){
        return;
    }

    CeosLinkedListNode *node = list->last;

    if(list->size == 1){
        list->first = NULL;
        list->last = NULL;
    } else {
        list->last = list->last->prev;
        list->last->next = NULL;
    }

    list->size--;

    node = CeosLinkedListFreeNode(node);
}

/*--------------------------------------------*/