#include "engine/dataStructure/preprossed_queue.h"


/*--------------------------------------------*/

QueuePreproStruct *EngineQueuePreproNew(int initNbE, int step){
    QueuePreproStruct *q = malloc(sizeof(QueuePreproStruct));
    MALLOC_CHECK(q);

    q->first = NULL;
    q->last = NULL;
    q->lastUse = NULL;
    q->nbElement = 0;
    q->nbUsedElement = 0;
    q->step = step;

    for (int i = 0; i < initNbE; i++) {
        EnginequeuePreproAddElement(q);
    }

    return q;
}

/*--------------------------------------------*/

void EnginequeuePreproAddElement(QueuePreproStruct *q){
    QueueElement *e = malloc(sizeof(QueueElement));
    MALLOC_CHECK(e);

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
    if(q->nbElement == 0){
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

void EngineQueuePreproPopDefElement(QueuePreproStruct *q){
    if(EngineQueuePreproIsEmpty(q))
        return;
    
    QueueElement *temp = q->first->next;
    free(q->first);
    q->first = temp;
    q->nbElement--;

    if (q->nbUsedElement > 0)
        q->nbUsedElement--;
}

/*--------------------------------------------*/

QueuePreproStruct *EngineQueuePreproClearAll(QueuePreproStruct *q){
    while(!EngineQueuePreproIsEmpty(q)){
        EngineQueuePreproPopDefElement(q);
    }
    free(q);

    return NULL;
}

/*--------------------------------------------*/

void EngineQueuePreproPopElement(QueuePreproStruct *q){
    if(EngineQueuePreproIsEmpty(q))
        return;
    
    QueueElement *temp = q->first;
    temp->value = NULL;
    q->first = q->first->next;

    q->last->next = temp;
    q->last = temp;

    if (q->nbUsedElement > 0)
        q->nbUsedElement--;
}

/*--------------------------------------------*/

void _intern_EngineQueuePreproPushElement(QueuePreproStruct *q, void *x){
    if(EngineQueuePreproIsEmpty(q))
        EngineQueuePreproAddStepElement(q);
    
    if(q->nbElement <= q->nbUsedElement)
        EngineQueuePreproAddStepElement(q);

    if(q->lastUse == NULL){
        q->lastUse = q->first;
        q->lastUse->value = x;
    }
    else{
        q->lastUse->next->value = x;
        q->lastUse = q->lastUse->next;
    }

    q->nbUsedElement++;
}

/*--------------------------------------------*/

void EngineQueuePreproPrintAllElementsInt(QueuePreproStruct *q){
    printf("\n------------------------------\n");
    printf("Queue (ALL): ");

    if(EngineQueuePreproIsEmpty(q))
        printf("EMPTY");

    QueueElement *e = q->first;
    for(int i = 0; i < q->nbElement; i++){
        printf("[%d], ", *(int*)e->value);
        e = e->next;
    }

    printf("\n------------------------------\n");
}

/*--------------------------------------------*/

void EngineQueuePreproPrintUsedElementsInt(QueuePreproStruct *q){
printf("\n------------------------------\n");
    printf("Queue (ONLY USED): ");

    if(EngineQueuePreproIsEmpty(q) || q->nbUsedElement == 0)
        printf("EMPTY");

    QueueElement *e = q->first;
    for(int i = 0; i < q->nbUsedElement; i++){
        printf("[%d], ", *(int*)e->value);
        e = e->next;
    }

    printf("\n------------------------------\n");
}

/*--------------------------------------------*/
