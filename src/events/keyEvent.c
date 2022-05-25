#include "engine/events/keyEvent.h"

EngineKeyEventPressed* EngineKeyEventPressedCreate(void){
	EngineKeyEventPressed* data = malloc(sizeof(EngineKeyEventPressed));
	data->key = ENGINE_KEY_UNKNOWN;
	return data;
}

EngineKeyEventReleased* EngineKeyEventReleasedCreate(void){
	EngineKeyEventReleased* data = malloc(sizeof(EngineKeyEventReleased));
	data->key = ENGINE_KEY_UNKNOWN;
	return data;
}
