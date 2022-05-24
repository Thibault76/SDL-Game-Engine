#pragma once

#include "../core.h"
#include "../window.h"
#include "../dataStructure/circularQueue.h"
#include "../dataStructure/floatDynamicArray.h"
#include "renderCommand.h"

typedef struct{
	EngineCircularQueue* renderQueues[2]; // a queue of render commands
	uint8_t currentQueue;

	EngineFloatDynamicArray* buffers[2];
	EngineCircularQueue* batchRenderQueue;

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

void EngineRendererClear(EngineRenderer* renderer);
void EngineRendererSetDrawColor(EngineRenderer* renderer, uint8_t r, uint8_t g, uint8_t b, uint8_t a);
void EngineRendererDrawPoint(EngineRenderer* renderer, float x, float y);
void EngineRendererDrawLine(EngineRenderer* renderer, float x1, float y1, float x2, float y2);
void EngineRendererDrawRect(EngineRenderer* renderer, float x, float y, float width, float height);

EngineCircularQueue* EngineRendererGetCurrentQueue(EngineRenderer* renderer);
EngineFloatDynamicArray* EngineRendererGetCurrentBuffer(EngineRenderer* renderer);

void EngineRendererSwap(EngineRenderer* renderer);
void EngineRendererDraw(EngineRenderer* renderer);