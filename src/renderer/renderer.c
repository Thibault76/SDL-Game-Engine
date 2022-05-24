#include "engine/renderer/renderer.h"
#include "engine/window.h"
#include <assert.h>
#include <libs/SDL2/SDL.h>

EngineRenderCommand* EngineRendererPushCommand(EngineCircularQueue *queue){
	assert(queue != NULL && "push into a NULL queue");
	void** value = EngineCircularQueuePushNULL(queue);

	if (value){
		return *value; // if the value is not NULL it's supposly set to a render command
	}
	
	*value = malloc(sizeof(EngineRenderCommand));
	MALLOC_CHECK(*value);
	return *value;
}

EngineRenderer* EngineRendererCreate(EngineWindow* window, uint32_t renderCommandCount){
	EngineRenderer* renderer = malloc(sizeof(EngineRenderer));
	MALLOC_CHECK(renderer);

	renderer->window = window;

	for (uint8_t queue=0; queue<2; queue++){
		renderer->renderQueues[queue] = EngineQueuePreproTestCreate(renderCommandCount, 10);
		for (uint32_t command=0; command<renderCommandCount; command++){
			EngineRendererPushCommand(renderer->renderQueues[queue]);
		}
	}
	renderer->currentQueue = 0;

	renderer->linesBuffer = EngineFloatDynamicArrayCreate(100);
	renderer->pointsBuffer = EngineFloatDynamicArrayCreate(100);
	renderer->rectsBuffer = EngineFloatDynamicArrayCreate(100);

	renderer->nativeRunderer = SDL_CreateRenderer(window->nativeWindow, -1, 0);
	if (renderer->nativeRunderer == NULL){
		fprintf(stderr, "SDL_CreateRenderer Error : %s", SDL_GetError());
		exit(EXIT_FAILURE);
	}

	return renderer;
}

void EngineRendererDestroyQueue(EngineCircularQueue *queue){
	QueueElement *element = queue->first;
	
	while (element != queue->end){
		free(element->value);
		element = element->next;
	}

	EngineQueuePreproTestDestroy(queue);
}

void EngineRendererDestroy(EngineRenderer* renderer){
	assert(renderer != NULL && "cannot destroy a NULL renderer");

	EngineFloatDynamicArrayDestroy(renderer->linesBuffer);
	EngineFloatDynamicArrayDestroy(renderer->pointsBuffer);
	EngineFloatDynamicArrayDestroy(renderer->rectsBuffer);

	for (uint8_t queue=0; queue<2; queue++){
		EngineRendererDestroyQueue(renderer->renderQueues[queue]);
	}

	SDL_DestroyRenderer(renderer->nativeRunderer);
	free(renderer);
}


void EngineRendererClear(EngineRenderer *renderer){
	assert(renderer != NULL && "cannot draw on a NULL renderer");
	EngineRenderCommand* command = EngineRendererPushCommand(EngineRendererGetCurrentQueue(renderer));
	command->type = ENGINE_RENDER_COMMAND_CLEAR;
}

void EngineRendererSetClearColor(EngineRenderer *renderer, uint8_t r, uint8_t g, uint8_t b){
	assert(renderer != NULL && "cannot draw on a NULL renderer");

}

void EngineRendererSetDrawColor(EngineRenderer *renderer, uint8_t r, uint8_t g, uint8_t b){
	assert(renderer != NULL && "cannot draw on a NULL renderer");

}

void EngineRendererDrawPoint(EngineRenderer *renderer, float x1, float y1){
	assert(renderer != NULL && "cannot draw on a NULL renderer");

}

void EngineRendererDrawLine(EngineRenderer *renderer, float x1, float y1, float x2, float y2){
	assert(renderer != NULL && "cannot draw on a NULL renderer");
	// EngineRenderCommand command = EngineRen;
	renderer->renderQueues[renderer->currentQueue];
}

void EngineRendererDrawRect(EngineRenderer *renderer, float x1, float y1, float width, float height){
	assert(renderer != NULL && "cannot draw on a NULL renderer");

}

EngineCircularQueue* EngineRendererGetCurrentQueue(EngineRenderer *renderer){
	return renderer->renderQueues[renderer->currentQueue];
}

void EngineRendererSwap(EngineRenderer *renderer){
	renderer->currentQueue = renderer->currentQueue;
}

void EngineRendererDraw(EngineRenderer *renderer){

}