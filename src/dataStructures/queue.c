#include <stdio.h>
#include <stdlib.h>
#include "engine/dataStructure/queue.h"

/*--------------------------------------------*/

Bool EngineQueueIsEmpty(QueueStruct *queue){
    if(queue->first == NULL && queue->last == NULL)
        return true;

    return false;
}

/*--------------------------------------------*/

QueueStruct *EngineQueueNew(void){
    QueueStruct *q = malloc(sizeof(QueueStruct));
    q->first = NULL;
    q->last = NULL;
    q->nbElement = 0;

    return q;
}

/*--------------------------------------------*/

int EngineQueueLength(QueueStruct *queue){
    return queue->nbElement;
}

/*--------------------------------------------*/

void* EngineQueueFirst(QueueStruct *queue){
    if(EngineQueueIsEmpty(queue))
        return NULL;
    
    return queue->first->value;
}

/*--------------------------------------------*/

void* EngineQueueLast(QueueStruct *queue){
    if(EngineQueueIsEmpty(queue))
        return NULL;
    
    return queue->last->value;
}

/*--------------------------------------------*/

void EngineQueuePush(QueueStruct *queue, void* x){
    QueueElement *element;

    element = malloc(sizeof(*element));

    if(element == NULL){
        fprintf(stderr, "Erreur : probleme allocation dynamique\n");
        exit(EXIT_FAILURE);
    }

    element->value = x;
    element->next = NULL;

    if(EngineQueueIsEmpty(queue)){
        queue->first = element;
        queue->last = element;
    } else {
        queue->last->next = element;
        queue->last = element;
    }

    queue->nbElement++;
}

/*--------------------------------------------*/

void EngineQueuePop(QueueStruct *queue){
    if(EngineQueueIsEmpty(queue)){
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

void EngineQueueClear(QueueStruct *queue){
    if(EngineQueueIsEmpty(queue)){
        free(queue);
        return;
    }

    while(!EngineQueueIsEmpty(queue))
        EngineQueuePop(queue);
    
    free(queue);
}

/*--------------------------------------------*/

void EngineQueueSwitch(QueueStruct *a, QueueStruct *b){
    QueueStruct *c = a;
    a = b;
    b = c;
}

/*--------------------------------------------*/