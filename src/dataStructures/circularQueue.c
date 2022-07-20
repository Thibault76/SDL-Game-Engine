#include "engine/dataStructure/CircularQueue.h"
#include <assert.h>

void CeosCircularQueueAllocSteps(CeosCircularQueue *q){
	assert(q != NULL && "cannot allocate an element in a NULL queue");
	for (uint32_t i=0; i<q->step; i++){
		CeosCircularQueueAllocElement(q);
	}
}

/*--------------------------------------------*/

CeosCircularQueue *CeosCircularQueueCreate(int initNbE, int step){
	CeosCircularQueue *q = malloc(sizeof(CeosCircularQueue));
	q->first = NULL;
	q->last = NULL;
	q->end = NULL;
	q->nbUseElement = 0;
	q->nbElement = 0;
	q->step = step;

	for (int i = 0; i < initNbE; i++) {
		CeosCircularQueueAllocElement(q);
	}

	return q;
}

/*--------------------------------------------*/

void CeosCircularQueueAllocElement(CeosCircularQueue *q){
	assert(q != NULL && "cannot allocate an element in a NULL queue");
	QueueElement *e = malloc(sizeof(QueueElement));
	if(!e)
		exit(EXIT_FAILURE);

	e->value = NULL;
	e->next = NULL;

	// we don't use CeosCircularQueueIsEmpty because we check the real count of elements, not the used ones
	if(q->nbElement == 0){
		q->first = e;
		q->end = e;
	} else {
		q->end->next = e;
		q->end = e;
	}

	q->nbElement++;
}

void CeosCircularQueueFreeElement(CeosCircularQueue *q){
	assert(q != NULL && "cannot free an element in a NULL queue");

	QueueElement* temp = q->first->next;
	free(q->first);
	q->first = temp;

	q->nbElement--;
}

/*--------------------------------------------*/

Bool CeosCircularQueueIsEmpty(CeosCircularQueue *q){
	assert(q != NULL && "cannot check element count in a NULL queue");
	return q->nbUseElement == 0;
}

/*--------------------------------------------*/

void CeosCircularQueuePush(CeosCircularQueue* q, void* value){
	assert(q != NULL && "cannot push elements in a NULL queue");

	if (q->nbUseElement+1 >= q->nbElement){
		CeosCircularQueueAllocSteps(q);
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

void** CeosCircularQueuePushNULL(CeosCircularQueue* q){
	assert(q != NULL && "cannot push elements in a NULL queue");

	if (q->nbUseElement+1 >= q->nbElement){
		CeosCircularQueueAllocSteps(q);
	}

	void** value;

	if (!q->last){
		q->last = q->first;
		value = &q->first->value;
	} else {
		value = &q->last->value;
	}
	
	q->last = q->last->next;

	q->nbUseElement++;
	*value = NULL;
	return value;
}

/*--------------------------------------------*/

void* CeosCircularQueuePop(CeosCircularQueue *q){
	assert(q != NULL && "cannot pop elements in a NULL queue");
	if(CeosCircularQueueIsEmpty(q)) return NULL;

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

CeosCircularQueue *CeosCircularQueueDestroy(CeosCircularQueue *q){
	assert(q != NULL && "cannot destroy a NULL queue");
	while(!q->nbElement){
		CeosCircularQueueFreeElement(q);
	}
	free(q);

	return NULL;
}

/*--------------------------------------------*/

QueueElement* CeosCircularQueueGetBegin(CeosCircularQueue *q){
	assert(q != NULL && "cannot get the first element of a NULL queue");
	return q->last != NULL ? q->first : NULL;
}

/*--------------------------------------------*/

QueueElement* CeosCircularQueueGetEnd(CeosCircularQueue *q){
	assert(q != NULL && "cannot get the last element of a NULL queue");
	return q->last;
}

/*--------------------------------------------*/

void CeosCircularQueueClear(CeosCircularQueue* q){
	assert(q != NULL && "cannot clear a NULL queue");
	q->nbUseElement = 0;
	q->last = q->first;
}