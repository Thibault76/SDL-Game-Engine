#pragma once
#include "core.h"

/* Définition d'une file */
typedef struct QueueElement{
    void* value;
    struct QueueElement *next;
}QueueElement, *Queue;

/* Paramètres de la file */
typedef struct QueueStruct{
    QueueElement* first;
    QueueElement* last;
    int nbElement;
}QueueStruct;

/* Prototypes */
Bool EngineQueueIsEmpty(QueueStruct *queue);
int EngineQueueLenght(QueueStruct *queue);
void* EngineQueueFirst(QueueStruct *queue);
void* EngineQueueLast(QueueStruct *queue);
void EngineQueuePush(QueueStruct *queue, void* x);
void EngineQueuePop(QueueStruct *queue);
void EngineQueueClear(QueueStruct *queue);
QueueStruct *EngineQueueNew(void);