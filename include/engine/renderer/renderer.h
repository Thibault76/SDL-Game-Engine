#pragma once

#include "../core.h"
#include "../dataStructure/queue.h"
#include "../dataStructure/floatDynamicArray.h"
#include "renderCommand.h"

typedef struct{
	QueueStruct* renderQueues[2]; // a queue of render commands
	uint8_t currentQueue;
	EngineFloatDynamicArray* linesBuffer;
	EngineFloatDynamicArray* pointsBuffer;
	EngineFloatDynamicArray* rectsBuffer;
} EngineRenderer;

EngineRenderer* EngineRenderCreate(void);

