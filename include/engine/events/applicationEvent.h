#pragma once

#include "../core.h"

typedef struct{
	uint32_t width;
	uint32_t height;
} EngineWindowEventResized;

typedef struct{
	uint32_t x;
	uint32_t y;
} EngineWindowEventMoved;

/**
 * @brief create the data for the window resied event
 * @return EngineWindowEventResized* 
 */
EngineWindowEventResized *EngineWindowEventResizedCreate();

/**
 * @brief create the data for the window moved event
 * @return EngineWindowEventResized* 
 */
EngineWindowEventMoved* EngineWindowEventMovedCreate();