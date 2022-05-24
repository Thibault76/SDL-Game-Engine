#include "engine/dataStructure/preprossed_queue.h"

/*--------------------------------------------*/

QueuePreproStruct *EngineQueuePreproNew(int initNbE, int step){
    QueuePreproStruct *q = malloc(sizeof(QueuePreproStruct));
    q->first = NULL;
    q->last = NULL;
    q->nbElement = 0;
    q->nbUseElement = 0;
    q->step = step;

    for (int i = 0; i < initNbE; i++) {
        EnginequeuePreproAddElement(q);
    }

    return q;
}

/*--------------------------------------------*/

void EnginequeuePreproAddElement(QueuePreproStruct *q){
    QueueElement *e = malloc(sizeof(QueueElement));
    if(!e)
        exit(EXIT_FAILURE);

    e->value = NULL;

    if(EngineQueuePreproIsEmpty(q)){
        q->first = e;
        q->last = e;
    } else {
        q->last->next = e;
        q->last = e;
    }
    q->nbElement++;
}

/*--------------------------------------------*/

Bool EngineQueuePreproIsEmpty(QueuePreproStruct *q){
    if(q->nbElement = 0){
        return true;
    }
    return false;
}

/*--------------------------------------------*/

void EngineQueuePreproAddStepElement(QueuePreproStruct *q){
    for (int i = 0; i < q->step; i++){
        EnginequeuePreproAddElement(q);
    }
}

/*--------------------------------------------*/

void EngineQueuePreproPopElement(QueuePreproStruct *q){
    if(EngineQueuePreproIsEmpty(q))
        return;
    
    QueueElement *temp = q->first->next;
    free(q->first);
    q->first = temp;
    q->nbElement--;

    if (q->nbUseElement > 0)
        q->nbUseElement--;
}

/*--------------------------------------------*/

QueuePreproStruct *EngineQueuePreproClearAll(QueuePreproStruct *q){
    while(!EngineQueuePreproIsEmpty(q)){
        EngineQueuePreproPopElement(q);
    }
    free(q);

    return NULL;
}
