#include "engine/events/applicationEvent.h"

// std
#include <stdio.h>
#include <stdlib.h>

EngineWindowEventResized *EngineWindowEventResizedCreate(void){
	EngineWindowEventResized* eventData = malloc(sizeof(EngineWindowEventResized*));

	if (!eventData){
		fprintf(stderr, "malloc Error");
		exit(EXIT_FAILURE);
	}

	eventData->width = 0;
	eventData->height = 0;
	return eventData;
}

EngineWindowEventMoved* EngineWindowEventMovedCreate(void){
	EngineWindowEventMoved* eventData = malloc(sizeof(EngineWindowEventMoved*));

	if (!eventData){
		fprintf(stderr, "malloc Error");
		exit(EXIT_FAILURE);
	}

	eventData->x = 0;
	eventData->y = 0;
	return eventData;
}