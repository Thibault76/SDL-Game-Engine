#include "engine/dataStructure/preprossed_queue.h"


/*--------------------------------------------*/

QueuePreproStruct *CeosQueuePreproNew(int initNbE, int step){
    QueuePreproStruct *q = malloc(sizeof(QueuePreproStruct));
    MALLOC_CHECK(q);

    q->first = NULL;
    q->last = NULL;
    q->lastUse = NULL;
    q->nbElement = 0;
    q->nbUsedElement = 0;
    q->step = step;

    for (int i = 0; i < initNbE; i++) {
        CeosqueuePreproAddElement(q);
    }

    return q;
}

/*--------------------------------------------*/

void CeosqueuePreproAddElement(QueuePreproStruct *q){
    QueueElement *e = malloc(sizeof(QueueElement));
    MALLOC_CHECK(e);

    e->value = NULL;

    if(CeosQueuePreproIsEmpty(q)){
        q->first = e;
        q->last = e;
    } else {
        q->last->next = e;
        q->last = e;
    }
    q->nbElement++;
}

/*--------------------------------------------*/

Bool CeosQueuePreproIsEmpty(QueuePreproStruct *q){
    if(q->nbElement == 0){
        return true;
    }
    return false;
}

/*--------------------------------------------*/

void CeosQueuePreproAddStepElement(QueuePreproStruct *q){
    for (int i = 0; i < q->step; i++){
        CeosqueuePreproAddElement(q);
    }
}

/*--------------------------------------------*/

void CeosQueuePreproPopDefElement(QueuePreproStruct *q){
    if(CeosQueuePreproIsEmpty(q))
        return;
    
    QueueElement *temp = q->first->next;
    free(q->first);
    q->first = temp;
    q->nbElement--;

    if (q->nbUsedElement > 0)
        q->nbUsedElement--;
}

/*--------------------------------------------*/

QueuePreproStruct *CeosQueuePreproClearAll(QueuePreproStruct *q){
    while(!CeosQueuePreproIsEmpty(q)){
        CeosQueuePreproPopDefElement(q);
    }
    free(q);

    return NULL;
}

/*--------------------------------------------*/

void CeosQueuePreproPopElement(QueuePreproStruct *q){
    if(CeosQueuePreproIsEmpty(q))
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

void _intern_CeosQueuePreproPushElement(QueuePreproStruct *q, void *x){
    if(CeosQueuePreproIsEmpty(q))
        CeosQueuePreproAddStepElement(q);
    
    if(q->nbElement <= q->nbUsedElement)
        CeosQueuePreproAddStepElement(q);

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

void CeosQueuePreproPrintAllElementsInt(QueuePreproStruct *q){
    printf("\n------------------------------\n");
    printf("Queue (ALL): ");

    if(CeosQueuePreproIsEmpty(q))
        printf("EMPTY");

    QueueElement *e = q->first;
    for(int i = 0; i < q->nbElement; i++){
        printf("[%d], ", *(int*)e->value);
        e = e->next;
    }

    printf("\n------------------------------\n");
}

/*--------------------------------------------*/

void CeosQueuePreproPrintUsedElementsInt(QueuePreproStruct *q){
printf("\n------------------------------\n");
    printf("Queue (ONLY USED): ");

    if(CeosQueuePreproIsEmpty(q) || q->nbUsedElement == 0)
        printf("EMPTY");

    QueueElement *e = q->first;
    for(int i = 0; i < q->nbUsedElement; i++){
        printf("[%d], ", *(int*)e->value);
        e = e->next;
    }

    printf("\n------------------------------\n");
}

/*--------------------------------------------*/
