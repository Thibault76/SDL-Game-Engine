#include "engine/events/event.h"

// std
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

EngineEvent* EngineEventCreate(void){
	EngineEvent* event = malloc(sizeof(Event*));

	if (!event){
		fprintf(stderr, "malloc Error");
		exit(EXIT_FAILURE);
	}

	event->category = ENGINE_EVENT_CATEGORY_NONE;
	event->type = ENGINE_EVENT_TYPE_NONE;
	event->handled = false;
	event->data = NULL;
	return event;
}

void EngineEventDestroy(EngineEvent* event){
	assert(event != NULL && "cannot destroy a NULL event");
	if (event->data) free(event->data);
	free(event);
}
