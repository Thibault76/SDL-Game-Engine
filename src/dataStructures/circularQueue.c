#include "engine/dataStructure/CircularQueue.h"
#include <assert.h>

void EngineCircularQueueAllocSteps(EngineCircularQueue *q){
	assert(q != NULL && "cannot allocate an element in a NULL queue");
	for (uint32_t i=0; i<q->step; i++){
		EngineCircularQueueAllocElement(q);
	}
}

/*--------------------------------------------*/

EngineCircularQueue *EngineCircularQueueCreate(int initNbE, int step){
	EngineCircularQueue *q = malloc(sizeof(EngineCircularQueue));
	q->first = NULL;
	q->last = NULL;
	q->end = NULL;
	q->nbUseElement = 0;
	q->nbElement = 0;
	q->step = step;

	for (int i = 0; i < initNbE; i++) {
		EngineCircularQueueAllocElement(q);
	}

	return q;
}

/*--------------------------------------------*/

void EngineCircularQueueAllocElement(EngineCircularQueue *q){
	assert(q != NULL && "cannot allocate an element in a NULL queue");
	QueueElement *e = malloc(sizeof(QueueElement));
	if(!e)
		exit(EXIT_FAILURE);

	e->value = NULL;

	// we don't use EngineCircularQueueIsEmpty because we check the real count of elements, not the used ones
	if(q->nbElement == 0){
		q->first = e;
		q->end = e;
	} else {
		q->end->next = e;
		q->end = e;
	}

	q->nbElement++;
}

void EngineCircularQueueFreeElement(EngineCircularQueue *q){
	assert(q != NULL && "cannot free an element in a NULL queue");

	QueueElement* temp = q->first->next;
	free(q->first);
	q->first = temp;

	q->nbElement--;
}

/*--------------------------------------------*/

Bool EngineCircularQueueIsEmpty(EngineCircularQueue *q){
	assert(q != NULL && "cannot check element count in a NULL queue");
	return q->nbUseElement == 0;
}

/*--------------------------------------------*/

void EngineQueueProproTestPush(EngineCircularQueue* q, void* value){
	assert(q != NULL && "cannot push elements in a NULL queue");

	if (q->nbUseElement+1 >= q->nbElement){
		EngineCircularQueueAllocSteps(q);
	}

	if (!q->last){
		q->last = q->first;
		q->first->value = value;
	} else {
		q->last->value = value;
	}
	
	q->last = q->last->next;

	q->nbUseElement++;
}

/*--------------------------------------------*/

void* EngineCircularQueuePop(EngineCircularQueue *q){
	assert(q != NULL && "cannot pop elements in a NULL queue");
	if(EngineCircularQueueIsEmpty(q))
		return NULL;

	void* value = q->first->value;
	QueueElement* temp = q->first->next;
	q->end->next = q->first;
	q->end = q->end->next;
	q->first->next = NULL;
	q->first = temp;

	q->nbUseElement--;

	return value;	
}

/*--------------------------------------------*/

EngineCircularQueue *EngineCircularQueueDestroy(EngineCircularQueue *q){
	assert(q != NULL && "cannot destroy a NULL queue");
	while(!q->nbElement){
		EngineCircularQueueFreeElement(q);
	}
	free(q);

	return NULL;
}

/*--------------------------------------------*/

QueueElement* EngineQueuePreproGetBegin(EngineCircularQueue *q){
	return q->last != NULL ? q->first : NULL;
}

/*--------------------------------------------*/

QueueElement* EngineQueuePreproGetEnd(EngineCircularQueue *q){
	return q->last;
}