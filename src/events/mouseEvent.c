#include "engine/events/mouseEvent.h"

EngineMouseEventMoved* EngineMouseEventMovedCreate(void){
	EngineMouseEventMoved* eventData = malloc(sizeof(EngineMouseEventMoved));
	MALLOC_CHECK(eventData);

	eventData->x = 0;
	eventData->y = 0;
	return eventData;
}

EngineMouseEventButtonPressed* EngineMouseEventButtonPressedCreate(void){
	EngineMouseEventButtonPressed* eventData = malloc(sizeof(EngineMouseEventButtonPressed));
	MALLOC_CHECK(eventData);

	eventData->button = ENGINE_MOUSE_BUTTON_LEFT;
	return eventData;
}

EngineMouseEventButtonReleased* EngineMouseEventButtonReleasedCreate(void){
	EngineMouseEventButtonReleased* eventData = malloc(sizeof(EngineMouseEventButtonReleased));
	MALLOC_CHECK(eventData);

	eventData->button = ENGINE_MOUSE_BUTTON_LEFT;
	return eventData;
}

EngineMouseEventScrolled* EngineMouseEventScrolledCreate(void){
	EngineMouseEventScrolled* eventData = malloc(sizeof(EngineMouseEventScrolled));
	MALLOC_CHECK(eventData);

	eventData->yOffset = 0;
	return eventData;
}
