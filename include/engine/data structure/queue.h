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
Bool queueIsEmpty(QueueStruct *queue);
void* queueLenght(QueueStruct *queue);
void* queueFirst(QueueStruct *queue);
void* queueLast(QueueStruct *queue);
void queuePush(QueueStruct *queue, void* x);
void queuePop(QueueStruct *queue);
void queueClear(QueueStruct *queue);
QueueStruct *queueNew(void);