#pragma once
#include "../core.h"
#include "queue.h"

/**
 * @brief preprossed queue structure
 * 
 */
typedef struct QueuePreproStructTest{
	QueueElement *first;
	QueueElement *last; // the last element of the 'fake' queue
	QueueElement *end; // the true last element of the queue
	uint32_t nbElement;
	uint32_t nbUseElement;
	uint32_t step;
}QueuePreproStructTest;

/**
 * @brief Create a new preprocessed queue
 * @param initNbE Initial number elements
 * @param step Number of elements added when there is excess
 * @return QueuePreproStructTest* preprossed structural queue
 */
QueuePreproStructTest *EngineQueuePreproTestCreate(int initNbE, int step);

/**
 * @brief allocate an empty element and push it at the end of the queue
 * @param q Preprossed structural queue
 * @return QueueElement* 
 */
void EngineQueuePreproTestAllocElement(QueuePreproStructTest *q);


/**
 * @brief destroy the firste element of the queue
 * @param q Preprossed structural queue
 * @return QueueElement* 
 */
void EngineQueuePreproTestFreeElement(QueuePreproStructTest *q);

/**
 * @brief Return 1 if the preprossed queue is empty else return 0
 * 
 * @param q Preprossed structural queue
 * @return Bool 
 */
Bool EngineQueuePreproTestIsEmpty(QueuePreproStructTest *q);

/**
 * @brief push the given element at the end of the queue
 * @param q Preprossed structural queue
 * @param value the value to store /!\ it will store the pointer and not a copy ! the user is responsable of memory leaks /!\
 */
void EngineQueueProproTestPush(QueuePreproStructTest* q, void* value);

/**
 * @brief Delete the first queue element
 * 
 * @param q Preprossed structural queue
 * @return void* the value of the last first element
 */
void* EngineQueuePreproTestPop(QueuePreproStructTest *q);

/**
 * @brief Delete all queue
 * 
 * @param q Preprossed structural queue
 * @return QueuePreproStructTest* return NULL pointer
 */
QueuePreproStructTest *EngineQueuePreproTestDestroy(QueuePreproStructTest *q);

QueueElement* EngineQueuePreproGetBegin(QueuePreproStructTest *q);
QueueElement* EngineQueuePreproGetEnd(QueuePreproStructTest *q);