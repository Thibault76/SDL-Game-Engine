#pragma once

#include "../core.h"
#include "../window.h"
#include "../dataStructure/circularQueue.h"
#include "../dataStructure/floatDynamicArray.h"
#include "renderCommand.h"

typedef struct{
	EngineCircularQueue* renderQueues[2]; // a queue of render commands
	uint8_t currentQueue;

	EngineFloatDynamicArray* linesBuffer;
	EngineFloatDynamicArray* pointsBuffer;
	EngineFloatDynamicArray* rectsBuffer;

	void* nativeRunderer;
	EngineWindow* window;
} EngineRenderer;

/**
 * @brief create and initialize a renderer
 * @param renderCommandCount 
 * @return EngineRenderer* 
 */
EngineRenderer* EngineRendererCreate(EngineWindow* window, uint32_t renderCommandCount);

void EngineRendererDestroy(EngineRenderer* renderer);

void EngineRendererClear(EngineRenderer *renderer);
void EngineRendererSetClearColor(EngineRenderer *renderer, uint8_t r, uint8_t g, uint8_t b);
void EngineRendererSetDrawColor(EngineRenderer *renderer, uint8_t r, uint8_t g, uint8_t b);
void EngineRendererDrawPoint(EngineRenderer *renderer, float x1, float y1);
void EngineRendererDrawLine(EngineRenderer *renderer, float x1, float y1, float x2, float y2);
void EngineRendererDrawRect(EngineRenderer *renderer, float x1, float y1, float width, float height);

EngineCircularQueue* EngineRendererGetCurrentQueue(EngineRenderer *renderer);

void EngineRendererSwap(EngineRenderer *renderer);
void EngineRendererDraw(EngineRenderer *renderer);