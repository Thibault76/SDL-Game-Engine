#pragma once
#include "../core.h"
#include "queue.h"

/**
 * @brief preprossed queue structure
 * 
 */
typedef struct CeosCircularQueue{
	QueueElement* first;
	QueueElement* last; // the last element of the 'fake' queue
	QueueElement* end; // the true last element of the queue
	uint32_t nbElement;
	uint32_t nbUseElement;
	uint32_t step;
} CeosCircularQueue;

/**
 * @brief Create a new preprocessed queue
 * @param initNbE Initial number elements
 * @param step Number of elements added when there is excess
 * @return CeosCircularQueue* preprossed structural queue
 */
CeosCircularQueue *CeosCircularQueueCreate(int initNbE, int step);

/**
 * @brief allocate an empty element and push it at the end of the queue
 * @param q Preprossed structural queue
 * @return QueueElement* 
 */
void CeosCircularQueueAllocElement(CeosCircularQueue* q);


/**
 * @brief destroy the firste element of the queue
 * @param q Preprossed structural queue
 * @return QueueElement* 
 */
void CeosCircularQueueFreeElement(CeosCircularQueue* q);

/**
 * @brief Return 1 if the preprossed queue is empty else return 0
 * 
 * @param q Preprossed structural queue
 * @return Bool 
 */
Bool CeosCircularQueueIsEmpty(CeosCircularQueue* q);

/**
 * @brief push the given element at the end of the queue
 * @param q Preprossed structural queue
 * @param value the value to store /!\ it will store the pointer and not a copy ! the user is responsable of memory leaks /!\
 */
void CeosCircularQueuePush(CeosCircularQueue* q, void* value);

/**
 * @brief push the given element at the end of the queue
 * @param q Preprossed structural queue
 */
void** CeosCircularQueuePushNULL(CeosCircularQueue* q);

/**
 * @brief Delete the first queue element
 * 
 * @param q Preprossed structural queue
 * @return void* the value of the last first element
 */
void* CeosCircularQueuePop(CeosCircularQueue* q);

/**
 * @brief Delete all queue
 * 
 * @param q Preprossed structural queue
 * @return CeosCircularQueue* return NULL pointer
 */
CeosCircularQueue *CeosCircularQueueDestroy(CeosCircularQueue* q);

/**
 * @brief get the first element of the list
 * @param q 
 * @return QueueElement* 
 */
QueueElement* CeosCircularQueueGetBegin(CeosCircularQueue* q);

/**
 * @brief get the last element of the list /!\ not a valid output /!\
 * @param q
 * @return QueueElement* 
 */
QueueElement* CeosCircularQueueGetEnd(CeosCircularQueue* q);

/**
 * @brief clear the the count of element in the queue
 * 
 */
void CeosCircularQueueClear(CeosCircularQueue* q);