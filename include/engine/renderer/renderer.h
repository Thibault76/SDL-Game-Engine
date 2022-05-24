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

EngineRenderer* EngineRendererCreate(void);

void EngineRendererClear(EngineRenderer *renderer);
void EngineRendererSetClearColor(EngineRenderer *renderer, uint8_t r, uint8_t g, uint8_t b);
void EngineRendererSetDrawColor(EngineRenderer *renderer, uint8_t r, uint8_t g, uint8_t b);
void EngineRendererDrawPoint(EngineRenderer *renderer, float x1, float y1);
void EngineRendererDrawLine(EngineRenderer *renderer, float x1, float y1, float x2, float y2);
void EngineRendererDrawRect(EngineRenderer *renderer, float x1, float y1, float width, float height);