#include <stdio.h>
#include <stdlib.h>
#include "engine/dataStructure/queue.h"
#include "engine/core.h"

/*--------------------------------------------*/

Bool CeosQueueIsEmpty(QueueStruct *queue){
    if(queue->first == NULL && queue->last == NULL)
        return true;

    return false;
}

/*--------------------------------------------*/

QueueStruct *CeosQueueNew(void){
    QueueStruct *q = malloc(sizeof(QueueStruct));
    MALLOC_CHECK(q);

    q->first = NULL;
    q->last = NULL;
    q->nbElement = 0;

    return q;
}

/*--------------------------------------------*/

int CeosQueueLength(QueueStruct *queue){
    return queue->nbElement;
}

/*--------------------------------------------*/

void* CeosQueueFirst(QueueStruct *queue){
    if(CeosQueueIsEmpty(queue))
        return NULL;
    
    return queue->first->value;
}

/*--------------------------------------------*/

void* CeosQueueLast(QueueStruct *queue){
    if(CeosQueueIsEmpty(queue))
        return NULL;
    
    return queue->last->value;
}

/*--------------------------------------------*/

void _intern_CeosQueuePush(QueueStruct *queue, void* x){
    QueueElement *element;

    element = malloc(sizeof(*element));
    MALLOC_CHECK(element);

    element->value = x;
    element->next = NULL;

    if(CeosQueueIsEmpty(queue)){
        queue->first = element;
        queue->last = element;
    } else {
        queue->last->next = element;
        queue->last = element;
    }

    queue->nbElement++;
}

/*--------------------------------------------*/

void CeosQueuePop(QueueStruct *queue){
    if(CeosQueueIsEmpty(queue)){
        return;
    }

    QueueElement *temp = queue->first;

    if(queue->first == queue->last){
        queue->first = NULL;
        queue->last = NULL;
    } else
        queue->first = queue->first->next;

    free(temp);
	temp = NULL;
    queue->nbElement--;
}

/*--------------------------------------------*/

void CeosQueueClear(QueueStruct *queue){
    if(CeosQueueIsEmpty(queue)){
        free(queue);
        return;
    }

    while(!CeosQueueIsEmpty(queue))
        CeosQueuePop(queue);
    
    free(queue);
}

/*--------------------------------------------*/

void CeosQueueSwitch(QueueStruct *a, QueueStruct *b){
    QueueStruct *c = a;
    a = b;
    b = c;
}

/*--------------------------------------------*/