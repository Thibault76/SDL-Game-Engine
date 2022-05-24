#include "engine/dataStructure/preprossed_queue_test.h"
#include <assert.h>

void EngineQueuePreproTestAllocSteps(QueuePreproStructTest *q){
	assert(q != NULL && "cannot allocate an element in a NULL queue");
	for (uint32_t i=0; i<q->step; i++){
		EngineQueuePreproTestAllocElement(q);
	}
}

/*--------------------------------------------*/

QueuePreproStructTest *EngineQueuePreproTestCreate(int initNbE, int step){
	QueuePreproStructTest *q = malloc(sizeof(QueuePreproStructTest));
	q->first = NULL;
	q->last = NULL;
	q->end = NULL;
	q->nbUseElement = 0;
	q->nbElement = 0;
	q->step = step;

	for (int i = 0; i < initNbE; i++) {
		EngineQueuePreproTestAllocElement(q);
	}

	return q;
}

/*--------------------------------------------*/

void EngineQueuePreproTestAllocElement(QueuePreproStructTest *q){
	printf("alloc\n");
	assert(q != NULL && "cannot allocate an element in a NULL queue");
	QueueElement *e = malloc(sizeof(QueueElement));
	if(!e)
		exit(EXIT_FAILURE);

	e->value = NULL;

	// we don't use EngineQueuePreproTestIsEmpty because we check the real count of elements, not the used ones
	if(q->nbElement == 0){
		q->first = e;
		q->end = e;
	} else {
		q->end->next = e;
		q->end = e;
	}

	q->nbElement++;
}

void EngineQueuePreproTestFreeElement(QueuePreproStructTest *q){
	assert(q != NULL && "cannot free an element in a NULL queue");

	QueueElement* temp = q->first->next;
	free(q->first);
	q->first = temp;

	q->nbElement--;
}

/*--------------------------------------------*/

Bool EngineQueuePreproTestIsEmpty(QueuePreproStructTest *q){
	assert(q != NULL && "cannot check element count in a NULL queue");
	return q->nbUseElement == 0;
}

/*--------------------------------------------*/

void EngineQueueProproTestPush(QueuePreproStructTest* q, void* value){
	assert(q != NULL && "cannot push elements in a NULL queue");

	if (q->nbUseElement+1 >= q->nbElement){
		EngineQueuePreproTestAllocSteps(q);
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

void* EngineQueuePreproTestPop(QueuePreproStructTest *q){
	assert(q != NULL && "cannot pop elements in a NULL queue");
	if(EngineQueuePreproTestIsEmpty(q))
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

QueuePreproStructTest *EngineQueuePreproTestDestroy(QueuePreproStructTest *q){
	assert(q != NULL && "cannot destroy a NULL queue");
	while(!q->nbElement){
		EngineQueuePreproTestFreeElement(q);
	}
	free(q);

	return NULL;
}

/*--------------------------------------------*/

QueueElement* EngineQueuePreproGetBegin(QueuePreproStructTest *q){
	return q->last != NULL ? q->first : NULL;
}

/*--------------------------------------------*/

QueueElement* EngineQueuePreproGetEnd(QueuePreproStructTest *q){
	return q->last;
}