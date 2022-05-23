#include "engine/renderer/renderer.h"

EngineRenderer* EngineRenderCreate(void){
	EngineRenderer* renderer = malloc(sizeof(EngineRenderer));
	MALLOC_CHECK(renderer);

	renderer->renderQueues[0] = EngineQueueNew();
	renderer->renderQueues[1] = EngineQueueNew();
	renderer->currentQueue = 0;

	// renderer->linesBuffer = EngineFloatDynamicArrayCreate(100);
	// renderer->pointsBuffer = EngineFloatDynamicArrayCreate(100);
	// renderer->rectsBuffer = EngineFloatDynamicArrayCreate(100);

	return renderer;
}
