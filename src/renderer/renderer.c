#include "engine/renderer/renderer.h"
#include <assert.h>

EngineRenderer* EngineRenderCreate(void){
	EngineRenderer* renderer = malloc(sizeof(EngineRenderer));
	MALLOC_CHECK(renderer);

	renderer->renderQueues[0] = EngineQueueNew();
	renderer->renderQueues[1] = EngineQueueNew();
	renderer->currentQueue = 0;

	renderer->linesBuffer = EngineFloatDynamicArrayCreate(100);
	renderer->pointsBuffer = EngineFloatDynamicArrayCreate(100);
	renderer->rectsBuffer = EngineFloatDynamicArrayCreate(100);

	return renderer;
}


void EngineRendererClear(EngineRenderer *renderer){
	
}

void EngineRendererSetClearColor(EngineRenderer *renderer, uint8_t r, uint8_t g, uint8_t b){

}

void EngineRendererSetDrawColor(EngineRenderer *renderer, uint8_t r, uint8_t g, uint8_t b){

}

void EngineRendererDrawPoint(EngineRenderer *renderer, float x1, float y1){

}

void EngineRendererDrawLine(EngineRenderer *renderer, float x1, float y1, float x2, float y2){
	assert(renderer != NULL && "cannot draw on a NULL renderer");
	// EngineRenderCommand command = EngineRen;
	renderer->renderQueues[renderer->currentQueue];
}

void EngineRendererDrawRect(EngineRenderer *renderer, float x1, float y1, float width, float height){

}