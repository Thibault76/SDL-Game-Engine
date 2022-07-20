#pragma once
#include "../core.h"

#define CeosQueuePush(q, x) _intern_CeosQueuePush(q, (void*)x);

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
Bool CeosQueueIsEmpty(QueueStruct *queue);

/**
 * @brief returns the length queue's
 * 
 * @param queue queue
 * @return length
 */
int CeosQueueLength(QueueStruct *queue);

/**
 * @brief returns the first element of the queue
 * 
 * @param queue queue
 * @return first element
 */
void* CeosQueueFirst(QueueStruct *queue);

/**
 * @brief returns the last element of the queue
 * 
 * @param queue queue
 * @return last element
 */
void* CeosQueueLast(QueueStruct *queue);

/**
 * @brief Add element to queue
 * 
 * @param queue queue
 * @param x element
 */
void _intern_CeosQueuePush(QueueStruct *queue, void* x);

/**
 * @brief Delete the first element of the queue
 * 
 * @param queue queue
 */
void CeosQueuePop(QueueStruct *queue);

/**
 * @brief Delete all the queue
 * 
 * @param queue queue
 */
void CeosQueueClear(QueueStruct *queue);

/**
 * @brief Create an empty queue
 * 
 * @return empty queue
 */
QueueStruct *CeosQueueNew(void);

/**
 * @brief invert two queues
 * 
 * @param a first queue
 * @param b second queue
 */
void CeosQueueSwitch(QueueStruct *a, QueueStruct *b);