#pragma once

#include "../core.h"

typedef struct{
} Event;

typedef enum{
	ENGINE_EVENT_TYPE_NONE = 0,

	ENGINE_EVENT_TYPE_WINDOW_CLOSED, // data = NULL
	ENGINE_EVENT_TYPE_WINDOW_RESIZED, // data = [uint32_t(width), uint32_t(height)]
	ENGINE_EVENT_TYPE_WINDOW_FOCUSED, // data = NULL
	ENGINE_EVENT_TYPE_WiNDOW_LOST_FOCUS, // data = NULL
	ENGINE_EVENT_TYPE_WINDOW_MOVED, // data = [uint32_t(x), uint32_t(y)]
	ENGINE_EVENT_TYPE_WINDOW_MINIMIZED, // data = NULL
	ENGINE_EVENT_TYPE_WINDOW_MAXIMIZED, // data = NULL

	ENGINE_EVENT_TYPE_APP_UPDATE, // data = float(delta)
	ENGINE_EVENT_TYPE_APP_RENDER, // data = NULL
	
	ENGINE_EVENT_TYPE_KEY_PRESSED, // data = [uint16_t(key), Bool (repeat)]
	ENGINE_EVENT_TYPE_KEY_RELEASED, // data = uint16_t(key)
	ENGINE_EVENT_TYPE_KEY_TYPED, // data = uint16_t(key)

	ENGINE_EVENT_TYPE_MOUSE_BUTTON_PRESSED, // data = uint8_t(button)
	ENGINE_EVENT_TYPE_MOUSE_BUTTON_RELEASED, // data = uint8_t(button)
	ENGINE_EVENT_TYPE_MOUSE_MOVED, // data = [uint32_t(x), uint32_t(y)]
	ENGINE_EVENT_TYPE_MOUSE_SCROLLED, // data = float(y)
} EngineEventType;

typedef enum{
	ENGINE_EVENT_CATEGORY_NONE = 0,
	ENGINE_EVENT_CATEGORY_APPLICATION = BIT(0),
	ENGINE_EVENT_CATEGORY_INPUT = BIT(1),
	ENGINE_EVENT_CATEGORY_KEYBOARD = BIT(2),
	ENGINE_EVENT_CATEGORY_MOUSE = BIT(3)
} EngineEventCategory;

typedef struct{
	EngineEventType type; // the specific type of the event
	EngineEventCategory category; // the category of the event, can have multiple categories
	Bool handled; // if the event has been handled or not

	void* data;
	void* userData;
} EngineEvent;

/**
 * @brief create an empty event
 * @return Event* 
 */
EngineEvent* EngineEventCreate(void);

/**
 * @brief destroy the given event and it data
 * @param event the event to destroy
 */
void EngineEventDestroy(EngineEvent* event);