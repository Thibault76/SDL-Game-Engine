#pragma once
#include "queue.h"

/**
 * @brief preprossed queue structure
 * 
 */
typedef struct QueuePreproStruct{
    QueueElement *first;
    QueueElement *last;
    int nbElement;
    int nbUseElement;
    int step;
}QueuePreproStruct;

/**
 * @brief Create a new preprocessed queue
 * 
 * @param initNbE Initial number elements
 * @param step Number of elements added when there is excess
 * @return QueuePreproStruct* preprossed structural queue
 */
QueuePreproStruct *EngineQueuePreproNew(int initNbE, int step);

/**
 * @brief Add an element empty to queue
 * 
 * @param q Preprossed structural queue
 * @return QueueElement* 
 */
void EnginequeuePreproAddElement(QueuePreproStruct *q);

/**
 * @brief Return 1 if the preprossed queue is empty else return 0
 * 
 * @param q Preprossed structural queue
 * @return Bool 
 */
Bool EngineQueuePreproIsEmpty(QueuePreproStruct *q);

/**
 * @brief Add step number elements to queue
 * 
 * @param q Preprossed structural queue
 */
void EngineQueuePreproAddStepElement(QueuePreproStruct *q);

/**
 * @brief Delete the first queue element
 * 
 * @param q Preprossed structural queue
 */
void EngineQueuePreproPopElement(QueuePreproStruct *q);

/**
 * @brief Delete all queue
 * 
 * @param q Preprossed structural queue
 * @return QueuePreproStruct* return NULL pointer
 */
QueuePreproStruct *EngineQueuePreproClearAll(QueuePreproStruct *q);
