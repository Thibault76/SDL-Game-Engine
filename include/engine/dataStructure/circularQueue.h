#pragma once
#include "../core.h"
#include "queue.h"

/**
 * @brief preprossed queue structure
 * 
 */
typedef struct EngineCircularQueue{
	QueueElement *first;
	QueueElement *last; // the last element of the 'fake' queue
	QueueElement *end; // the true last element of the queue
	uint32_t nbElement;
	uint32_t nbUseElement;
	uint32_t step;
} EngineCircularQueue;

/**
 * @brief Create a new preprocessed queue
 * @param initNbE Initial number elements
 * @param step Number of elements added when there is excess
 * @return EngineCircularQueue* preprossed structural queue
 */
EngineCircularQueue *EngineCircularQueueCreate(int initNbE, int step);

/**
 * @brief allocate an empty element and push it at the end of the queue
 * @param q Preprossed structural queue
 * @return QueueElement* 
 */
void EngineCircularQueueAllocElement(EngineCircularQueue *q);


/**
 * @brief destroy the firste element of the queue
 * @param q Preprossed structural queue
 * @return QueueElement* 
 */
void EngineCircularQueueFreeElement(EngineCircularQueue *q);

/**
 * @brief Return 1 if the preprossed queue is empty else return 0
 * 
 * @param q Preprossed structural queue
 * @return Bool 
 */
Bool EngineCircularQueueIsEmpty(EngineCircularQueue *q);

/**
 * @brief push the given element at the end of the queue
 * @param q Preprossed structural queue
 * @param value the value to store /!\ it will store the pointer and not a copy ! the user is responsable of memory leaks /!\
 */
void EngineQueueProproTestPush(EngineCircularQueue* q, void* value);

/**
 * @brief Delete the first queue element
 * 
 * @param q Preprossed structural queue
 * @return void* the value of the last first element
 */
void* EngineCircularQueuePop(EngineCircularQueue *q);

/**
 * @brief Delete all queue
 * 
 * @param q Preprossed structural queue
 * @return EngineCircularQueue* return NULL pointer
 */
EngineCircularQueue *EngineCircularQueueDestroy(EngineCircularQueue *q);

/**
 * @brief get the first element of the list
 * @param q 
 * @return QueueElement* 
 */
QueueElement* EngineQueuePreproGetBegin(EngineCircularQueue *q);
QueueElement* EngineQueuePreproGetEnd(EngineCircularQueue *q);