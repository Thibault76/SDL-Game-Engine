#pragma once

#include "../core.h"
#include "keys.h"

typedef struct{
	EngineKey key;
} EngineKeyEventPressed;

typedef struct{
	EngineKey key;
} EngineKeyEventReleased;

/**
 * @brief create the data for the key pressed event
 * @return EngineKeyEventPressed* 
 */
EngineKeyEventPressed* EngineKeyEventPressedCreate(void);

/**
 * @brief create the data for the key released event
 * @return EngineKeyEventReleased* 
 */
EngineKeyEventReleased* EngineKeyEventReleasedCreate(void);