#pragma once
#include "../core.h"

/**
 * @brief element of a queue
 * 
 */
typedef struct QueueElement{
    void *value;
    struct QueueElement *next;
}QueueElement;

/**
 * @brief queue structure
 * 
 */
typedef struct QueueStruct{
    QueueElement *first;
    QueueElement *last;
    int nbElement;
}QueueStruct;

/**
 * @brief returns 0 if queue is empty else return 1
 * 
 * @param queue queue
 * @return Bool 
 */
Bool EngineQueueIsEmpty(QueueStruct *queue);

/**
 * @brief returns the length queue's
 * 
 * @param queue queue
 * @return length
 */
int EngineQueueLength(QueueStruct *queue);

/**
 * @brief returns the first element of the queue
 * 
 * @param queue queue
 * @return first element
 */
void* EngineQueueFirst(QueueStruct *queue);

/**
 * @brief returns the last element of the queue
 * 
 * @param queue queue
 * @return last element
 */
void* EngineQueueLast(QueueStruct *queue);

/**
 * @brief Add element to queue
 * 
 * @param queue queue
 * @param x element
 */
void EngineQueuePush(QueueStruct *queue, void* x);

/**
 * @brief Delete the first element of the queue
 * 
 * @param queue queue
 */
void EngineQueuePop(QueueStruct *queue);

/**
 * @brief Delete all the queue
 * 
 * @param queue queue
 */
void EngineQueueClear(QueueStruct *queue);

/**
 * @brief Create an empty queue
 * 
 * @return empty queue
 */
QueueStruct *EngineQueueNew(void);

/**
 * @brief invert two queues
 * 
 * @param a first queue
 * @param b second queue
 */
void EngineQueueSwitch(QueueStruct *a, QueueStruct *b);