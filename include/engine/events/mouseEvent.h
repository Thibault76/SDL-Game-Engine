#pragma once

#include "../core.h"
#include "mouseButton.h"

typedef struct{
	uint32_t x;
	uint32_t y;
} EngineMouseEventMoved;

typedef struct{
	EngineMouseButton button;
} EngineMouseEventButtonPressed;

typedef struct{
	EngineMouseButton button;
} EngineMouseEventButtonReleased;

typedef struct{
	float yOffset;
} EngineMouseEventScrolled;

/**
 * @brief create the data for the mouse moved event
 * @return EngineMouseEventMoved* 
 */
EngineMouseEventMoved* EngineMouseEventMovedCreate(void);

/**
 * @brief create the data for the mouse button pressed event
 * @return EngineMouseEventButtonPressed* 
 */
EngineMouseEventButtonPressed* EngineMouseEventButtonPressedCreate(void);

/**
 * @brief create the data for the mouse button released event
 * @return EngineMouseEventButtonReleased* 
 */
EngineMouseEventButtonReleased* EngineMouseEventButtonReleasedCreate(void);

/**
 * @brief create the data for the mouse scrolled event
 * @return EngineMouseEventScrolled* 
 */
EngineMouseEventScrolled* EngineMouseEventScrolledCreate(void);