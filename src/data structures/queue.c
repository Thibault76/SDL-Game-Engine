#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

Bool queueIsEmpty(QueueStruct *queue){
    if(queue->first == NULL && queue->last == NULL)
        return true;

    return false;
}

/*--------------------------------------------*/

QueueStruct *queueNew(void){
    QueueStruct *q = malloc(sizeof(QueueStruct));
    q->first = NULL;
    q->last = NULL;
    q->nbElement = 0;

    return q;
}

/*--------------------------------------------*/

int queueLenght(QueueStruct *queue){
    return queue->nbElement;
}

/*--------------------------------------------*/

void* queueFirst(QueueStruct *queue){
    if(queueIsEmpty(queue))
        return NULL;
    
    return queue->first->value;
}

/*--------------------------------------------*/

void* queueLast(QueueStruct *queue){
    if(queueIsEmpty(queue))
        return NULL;
    
    return queue->last->value;
}

/*--------------------------------------------*/

void queuePush(QueueStruct *queue, void* x){
    QueueElement *element;

    element = malloc(sizeof(*element));

    if(element == NULL){
        fprintf(stderr, "Erreur : probleme allocation dynamique\n");
        exit(EXIT_FAILURE);
    }

    element->value = x;
    element->next = NULL;

    if(queueIsEmpty(queue)){
        queue->first = element;
        queue->last = element;
    } else {
        queue->last->next = element;
        queue->last = element;
    }

    queue->nbElement++;
}

/*--------------------------------------------*/

void queuePop(QueueStruct *queue){
    if(queueIsEmpty(queue)){
        return;
    }

    QueueElement *temp = queue->first;

    if(queue->first == queue->last){
        queue->first = NULL;
        queue->last = NULL;
    } else
        queue->first = queue->first->next;

    free(temp);
    queue->nbElement--;
}

/*--------------------------------------------*/

void queueClear(QueueStruct *queue){
    if(queueIsEmpty(queue)){
        free(queue);
        return;
    }

    while(!queueIsEmpty(queue))
        queuePop(queue);
    
    free(queue);
}

/*--------------------------------------------*/