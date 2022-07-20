#pragma once
#include "queue.h"

#define CeosQueuePreproPushElement(q, x) _intern_CeosQueuePreproPushElement(q, (void*)x)

/**
 * @brief preprossed queue structure
 * 
 */
typedef struct QueuePreproStruct{
    QueueElement *first;
    QueueElement *last;
    QueueElement *lastUse;
    int nbElement;
    int nbUsedElement;
    int step;
}QueuePreproStruct;

/**
 * @brief Create a new preprocessed queue
 * 
 * @param initNbE Initial number elements
 * @param step Number of elements added when there is excess
 * @return QueuePreproStruct* preprossed structural queue
 */
QueuePreproStruct *CeosQueuePreproNew(int initNbE, int step);

/**
 * @brief Add an element empty to queue
 * 
 * @param q Preprossed structural queue
 * @return QueueElement* 
 */
void CeosqueuePreproAddElement(QueuePreproStruct *q);

/**
 * @brief Return 1 if the preprossed queue is empty else return 0
 * 
 * @param q Preprossed structural queue
 * @return Bool 
 */
Bool CeosQueuePreproIsEmpty(QueuePreproStruct *q);

/**
 * @brief Add step number elements to queue
 * 
 * @param q Preprossed structural queue
 */
void CeosQueuePreproAddStepElement(QueuePreproStruct *q);

/**
 * @brief Delete definitively the first queue element
 * 
 * @param q Preprossed structural queue
 */
void CeosQueuePreproPopDefElement(QueuePreproStruct *q);

/**
 * @brief Delete all queue
 * 
 * @param q Preprossed structural queue
 * @return QueuePreproStruct* return NULL pointer
 */
QueuePreproStruct *CeosQueuePreproClearAll(QueuePreproStruct *q);

/**
 * @brief Delete the first queue element
 * 
 * @param q Preprossed structural queue
 */
void CeosQueuePreproPopElement(QueuePreproStruct *q);

/**
 * @brief Add use element to preprossed queue
 * 
 * @param q Preprossed structural queue
 * @param x Value saved in element of queue
 */
void _intern_CeosQueuePreproPushElement(QueuePreproStruct *q, void *x);

/**
 * @brief Print all elements in preprossed queue like int
 * 
 * @param q Preprossed structural queue
 */
void CeosQueuePreproPrintAllElementsInt(QueuePreproStruct *q);

/**
 * @brief Print only use elements in preprossed queue like int
 * 
 * @param q Preprossed structural queue
 */
void CeosQueuePreproPrintUsedElementsInt(QueuePreproStruct *q);
