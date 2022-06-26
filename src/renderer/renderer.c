#include "engine/renderer/renderer.h"
#include "engine/window.h"
#include <assert.h>
#include <libs/SDL2/SDL.h>

EngineRenderCommand* EngineRendererPushCommand(EngineCircularQueue *queue){
	assert(queue != NULL && "push into a NULL queue");
	void** value = EngineCircularQueuePushNULL(queue);

	if (*value){
		return *value; // if the value is not NULL it's supposly set to a render command
	}
	
	*value = malloc(sizeof(EngineRenderCommand));
	MALLOC_CHECK(*value);

	EngineRenderCommand* command = (EngineRenderCommand*)(*value);
	command->data = NULL;
	command->count = 1;
	command->type = ENGINE_RENDER_COMMAND_NONE;
	return *value;
}

EngineRenderer* EngineRendererCreate(EngineWindow* window, uint32_t renderCommandCount){
	EngineRenderer* renderer = malloc(sizeof(EngineRenderer));
	MALLOC_CHECK(renderer);

	renderer->window = window;

	for (uint8_t queue=0; queue<2; queue++){
		renderer->renderQueues[queue] = EngineCircularQueueCreate(renderCommandCount, 10);
		for (uint32_t command=0; command<renderCommandCount; command++){
			EngineCircularQueue *renderQueue = renderer->renderQueues[queue];
			QueueElement* element = renderQueue->first;
			while (element){
				element->value = malloc(sizeof(EngineRenderCommand));
				element = element->next;
			}
		}
		renderer->buffers[queue] = EngineFloatDynamicArrayCreate(renderCommandCount);
		renderer->textureBuffers[queue] = EngineDynamicArrayCreate(renderCommandCount);
	}
	renderer->currentQueue = 0;
	renderer->batchRenderQueue = EngineCircularQueueCreate(renderCommandCount, 10);

	renderer->nativeRunderer = SDL_CreateRenderer(window->nativeWindow, -1, 0);
	if (renderer->nativeRunderer == NULL){
		fprintf(stderr, "SDL_CreateRenderer Error : %s", SDL_GetError());
		exit(EXIT_FAILURE);
	}

	return renderer;
}

void EngineRendererDestroyQueue(EngineCircularQueue *queue){
	QueueElement *element = queue->first;
	uint16_t i=0;
	while (element != queue->end){
		free(element->value);
		element->value = NULL;
		element = element->next;
		i++;
	}

	EngineCircularQueueDestroy(queue);
}

void EngineRendererDestroy(EngineRenderer* renderer){
	assert(renderer != NULL && "cannot destroy a NULL renderer");


	for (uint8_t queue=0; queue<2; queue++){
		EngineRendererDestroyQueue(renderer->renderQueues[queue]);
		EngineFloatDynamicArrayDestroy(renderer->buffers[queue]);
		EngineDynamicArrayDestroy(renderer->textureBuffers[queue]);
	}

	EngineCircularQueueDestroy(renderer->batchRenderQueue);
	SDL_DestroyRenderer(renderer->nativeRunderer);
	free(renderer);
	renderer = NULL;
}

void EngineRendererClear(EngineRenderer* renderer){
	assert(renderer != NULL && "cannot draw on a NULL renderer");
	EngineRenderCommand* command = EngineRendererPushCommand(EngineRendererGetCurrentQueue(renderer));
	command->type = ENGINE_RENDER_COMMAND_CLEAR;
}

void EngineRendererSetDrawColor(EngineRenderer* renderer, uint8_t r, uint8_t g, uint8_t b, uint8_t a){
	assert(renderer != NULL && "cannot draw on a NULL renderer");
	EngineRenderCommand* command = EngineRendererPushCommand(EngineRendererGetCurrentQueue(renderer));
	EngineFloatDynamicArray* buffer = EngineRendererGetCurrentBuffer(renderer);
	command->type = ENGINE_RENDER_COMMAND_SET_DRAW_COLOR;
	command->data = EngineFloatDynamicArrayInsert(buffer, (float)r);
	EngineFloatDynamicArrayInsert(buffer, (float)g);
	EngineFloatDynamicArrayInsert(buffer, (float)b);
	EngineFloatDynamicArrayInsert(buffer, (float)a);
}

void EngineRendererDrawPoint(EngineRenderer* renderer, float x, float y){
	assert(renderer != NULL && "cannot draw on a NULL renderer");
	EngineRenderCommand* command = EngineRendererPushCommand(EngineRendererGetCurrentQueue(renderer));
	EngineFloatDynamicArray* buffer = EngineRendererGetCurrentBuffer(renderer);
	command->type = ENGINE_RENDER_COMMAND_DRAW_POINTS;
	command->data = EngineFloatDynamicArrayInsert(buffer, x);
	EngineFloatDynamicArrayInsert(buffer, y);
}

void EngineRendererDrawLine(EngineRenderer* renderer, float x1, float y1, float x2, float y2){
	assert(renderer != NULL && "cannot draw on a NULL renderer");
	EngineRenderCommand* command = EngineRendererPushCommand(EngineRendererGetCurrentQueue(renderer));
	EngineFloatDynamicArray* buffer = EngineRendererGetCurrentBuffer(renderer);
	command->type = ENGINE_RENDER_COMMAND_DRAW_LINES;
	command->data = EngineFloatDynamicArrayInsert(buffer, x1);
	EngineFloatDynamicArrayInsert(buffer, y1);
	EngineFloatDynamicArrayInsert(buffer, x2);
	EngineFloatDynamicArrayInsert(buffer, y2);
}

void EngineRendererDrawLineStrip(EngineRenderer* renderer, float x1, float y1, float x2, float y2){
	assert(renderer != NULL && "cannot draw on a NULL renderer");
	EngineRenderCommand* command = EngineRendererPushCommand(EngineRendererGetCurrentQueue(renderer));
	EngineFloatDynamicArray* buffer = EngineRendererGetCurrentBuffer(renderer);
	command->type = ENGINE_RENDER_COMMAND_DRAW_LINES_STRIP;
	command->data = EngineFloatDynamicArrayInsert(buffer, x1);
	EngineFloatDynamicArrayInsert(buffer, y1);
	EngineFloatDynamicArrayInsert(buffer, x2);
	EngineFloatDynamicArrayInsert(buffer, y2);
}

void EngineRendererDrawRect(EngineRenderer* renderer, float x, float y, float width, float height){
	assert(renderer != NULL && "cannot draw on a NULL renderer");
	EngineRenderCommand* command = EngineRendererPushCommand(EngineRendererGetCurrentQueue(renderer));
	EngineFloatDynamicArray* buffer = EngineRendererGetCurrentBuffer(renderer);
	command->type = ENGINE_RENDER_COMMAND_DRAW_RECTS;
	command->data = EngineFloatDynamicArrayInsert(buffer, x);
	EngineFloatDynamicArrayInsert(buffer, y);
	EngineFloatDynamicArrayInsert(buffer, width);
	EngineFloatDynamicArrayInsert(buffer, height);
}

void EngineRendererDrawFilledRect(EngineRenderer* renderer, float x, float y, float width, float height){
	assert(renderer != NULL && "cannot draw on a NULL renderer");
	EngineRenderCommand* command = EngineRendererPushCommand(EngineRendererGetCurrentQueue(renderer));
	EngineFloatDynamicArray* buffer = EngineRendererGetCurrentBuffer(renderer);
	command->type = ENGINE_RENDER_COMMAND_DRAW_FILLED_RECTS;
	command->data = EngineFloatDynamicArrayInsert(buffer, x);
	EngineFloatDynamicArrayInsert(buffer, y);
	EngineFloatDynamicArrayInsert(buffer, width);
	EngineFloatDynamicArrayInsert(buffer, height);
}

void EngineRendererDrawSubTexture(EngineRenderer* renderer, float x, float y, float width, float height, EngineSubTexture* texture){
	assert(renderer != NULL && "cannot draw on a NULL renderer");
	EngineRenderCommand* command = EngineRendererPushCommand(EngineRendererGetCurrentQueue(renderer));
	EngineFloatDynamicArray* buffer = EngineRendererGetCurrentBuffer(renderer);
	command->type = ENGINE_RENDER_COMMAND_DRAW_SUBTEXTURE;
	command->data = EngineFloatDynamicArrayInsert(buffer, EngineDynamicArrayGetSize((EngineRendererGetCurrentTextureBuffer(renderer))));
	EngineDynamicArrayInsert(EngineRendererGetCurrentTextureBuffer(renderer), texture->texture);
	EngineFloatDynamicArrayInsert(buffer, x);
	EngineFloatDynamicArrayInsert(buffer, y);
	EngineFloatDynamicArrayInsert(buffer, width);
	EngineFloatDynamicArrayInsert(buffer, height);
	EngineFloatDynamicArrayInsert(buffer, (float)texture->x);
	EngineFloatDynamicArrayInsert(buffer, (float)texture->y);
	EngineFloatDynamicArrayInsert(buffer, (float)texture->w);
	EngineFloatDynamicArrayInsert(buffer, (float)texture->h);
}

void EngineRendererDrawRotatedSubTexture(EngineRenderer* renderer, float x, float y, float width, float height, float angle, float rotationX, float rotationY,  EngineSubTexture* texture){
	assert(renderer != NULL && "cannot draw on a NULL renderer");
	EngineRenderCommand* command = EngineRendererPushCommand(EngineRendererGetCurrentQueue(renderer));
	EngineFloatDynamicArray* buffer = EngineRendererGetCurrentBuffer(renderer);
	command->type = ENGINE_RENDER_COMMAND_DRAW_ROTATED_SUBTEXTURE;
	command->data = EngineFloatDynamicArrayInsert(buffer, EngineDynamicArrayGetSize((EngineRendererGetCurrentTextureBuffer(renderer))));
	EngineDynamicArrayInsert(EngineRendererGetCurrentTextureBuffer(renderer), texture->texture);
	EngineFloatDynamicArrayInsert(buffer, x);
	EngineFloatDynamicArrayInsert(buffer, y);
	EngineFloatDynamicArrayInsert(buffer, width);
	EngineFloatDynamicArrayInsert(buffer, height);
	EngineFloatDynamicArrayInsert(buffer, (float)texture->x);
	EngineFloatDynamicArrayInsert(buffer, (float)texture->y);
	EngineFloatDynamicArrayInsert(buffer, (float)texture->w);
	EngineFloatDynamicArrayInsert(buffer, (float)texture->h);
	EngineFloatDynamicArrayInsert(buffer, angle);
	EngineFloatDynamicArrayInsert(buffer, rotationX);
	EngineFloatDynamicArrayInsert(buffer, rotationY);
}

void EngineRendererDrawTexture(EngineRenderer* renderer, float x, float y, float width, float height, EngineTexture* texture){
	assert(renderer != NULL && "cannot draw on a NULL renderer");
	EngineRenderCommand* command = EngineRendererPushCommand(EngineRendererGetCurrentQueue(renderer));
	EngineFloatDynamicArray* buffer = EngineRendererGetCurrentBuffer(renderer);
	command->type = ENGINE_RENDER_COMMAND_DRAW_TEXTURE;
	command->data = EngineFloatDynamicArrayInsert(buffer, EngineDynamicArrayGetSize((EngineRendererGetCurrentTextureBuffer(renderer))));
	EngineDynamicArrayInsert(EngineRendererGetCurrentTextureBuffer(renderer), texture->texture);
	EngineFloatDynamicArrayInsert(buffer, x);
	EngineFloatDynamicArrayInsert(buffer, y);
	EngineFloatDynamicArrayInsert(buffer, width);
	EngineFloatDynamicArrayInsert(buffer, height);
}

void EngineRendererDrawRotatedTexture(EngineRenderer* renderer, float x, float y, float width, float height, float angle, float rotationX, float rotationY, EngineTexture* texture){
	assert(renderer != NULL && "cannot draw on a NULL renderer");
	EngineRenderCommand* command = EngineRendererPushCommand(EngineRendererGetCurrentQueue(renderer));
	EngineFloatDynamicArray* buffer = EngineRendererGetCurrentBuffer(renderer);
	command->type = ENGINE_RENDER_COMMAND_DRAW_ROTATED_TEXTURE;
	command->data = EngineFloatDynamicArrayInsert(buffer, EngineDynamicArrayGetSize((EngineRendererGetCurrentTextureBuffer(renderer))));
	EngineDynamicArrayInsert(EngineRendererGetCurrentTextureBuffer(renderer), texture->texture);
	EngineFloatDynamicArrayInsert(buffer, x);
	EngineFloatDynamicArrayInsert(buffer, y);
	EngineFloatDynamicArrayInsert(buffer, width);
	EngineFloatDynamicArrayInsert(buffer, height);
	EngineFloatDynamicArrayInsert(buffer, angle);
	EngineFloatDynamicArrayInsert(buffer, rotationX);
	EngineFloatDynamicArrayInsert(buffer, rotationY);
}

EngineCircularQueue* EngineRendererGetCurrentQueue(EngineRenderer* renderer){
	assert(renderer != NULL && "cannot get the current queue of a NULL renderer");
	return renderer->renderQueues[renderer->currentQueue];
}

EngineFloatDynamicArray* EngineRendererGetCurrentBuffer(EngineRenderer* renderer){
	assert(renderer != NULL && "cannot get the current buffer of a NULL renderer");
	return renderer->buffers[renderer->currentQueue];
}

EngineDynamicArray* EngineRendererGetCurrentTextureBuffer(EngineRenderer* renderer){
	assert(renderer != NULL && "cannot get the current buffer of a NULL renderer");	
	return renderer->textureBuffers[renderer->currentQueue];
}

void EngineRendererSwap(EngineRenderer* renderer){
	assert(renderer != NULL && "cannot swap a NULL renderer");
	renderer->currentQueue = (renderer->currentQueue+1) % 2;

	EngineFloatDynamicArrayClear(EngineRendererGetCurrentBuffer(renderer));
	EngineDynamicArrayClear(EngineRendererGetCurrentTextureBuffer(renderer));
	EngineCircularQueueClear(EngineRendererGetCurrentQueue(renderer));
	EngineCircularQueueClear(renderer->batchRenderQueue);
}

void EngineRenderPoints(EngineRenderer* renderer, EngineRenderCommand* command){
	assert(renderer != NULL && "cannot draw from a NULL renderer");
	assert(command != NULL && "cannot draw a line from a NULL render command");
	SDL_RenderDrawPointsF(renderer->nativeRunderer, command->data, command->count);
}

void EngineRenderLinesStrip(EngineRenderer* renderer, EngineRenderCommand* command){
	assert(renderer != NULL && "cannot draw from a NULL renderer");
	assert(command != NULL && "cannot draw a line from a NULL render command");
	SDL_RenderDrawLinesF(renderer->nativeRunderer, (const SDL_FPoint*)command->data, command->count*2);
}

void EngineRenderLines(EngineRenderer* renderer, EngineRenderCommand* command){
	assert(renderer != NULL && "cannot draw from a NULL renderer");
	assert(command != NULL && "cannot draw a line from a NULL render command");

	for (uint16_t i=0; i<command->count; i++){
		float* data = command->data;
		float x1 = data[i*4+0];
		float y1 = data[i*4+1];
		float x2 = data[i*4+2];
		float y2 = data[i*4+3];
		SDL_RenderDrawLineF(renderer->nativeRunderer, x1, y1, x2, y2);
	}
}

void EngineRenderRects(EngineRenderer* renderer, EngineRenderCommand* command){
	assert(renderer != NULL && "cannot draw from a NULL renderer");
	assert(command != NULL && "cannot draw a line from a NULL render command");
	SDL_RenderDrawRectsF(renderer->nativeRunderer, command->data, command->count);
}

void EngineRenderFilledRects(EngineRenderer* renderer, EngineRenderCommand* command){
	assert(renderer != NULL && "cannot draw from a NULL renderer");
	assert(command != NULL && "cannot draw a line from a NULL render command");
	SDL_RenderFillRectsF(renderer->nativeRunderer, command->data, command->count);
}

void EngineRenderClear(EngineRenderer* renderer, EngineRenderCommand* command){
	assert(renderer != NULL && "cannot draw from a NULL renderer");
	assert(command != NULL && "cannot draw a line from a NULL render command");
	SDL_RenderClear(renderer->nativeRunderer);
}

void EngineRenderSetDrawColor(EngineRenderer* renderer, EngineRenderCommand* command){
	assert(renderer != NULL && "cannot draw from a NULL renderer");
	assert(command != NULL && "cannot draw a line from a NULL render command");
	
	float *color = command->data;
	uint8_t r = color[0];
	uint8_t g = color[1];
	uint8_t b = color[2];
	uint8_t a = color[3];
	SDL_SetRenderDrawColor(renderer->nativeRunderer, r, g, b, a);
}

void EngineRenderDrawSubTexture(EngineRenderer* renderer, EngineRenderCommand* command){
	assert(renderer != NULL && "cannot draw from a NULL renderer");
	assert(command != NULL && "cannot draw a line from a NULL render command");
	float *data = command->data;

	void* texture = EngineRendererGetCurrentTextureBuffer(renderer)->content[(int)data[0]];

	SDL_FRect dstRect;
	dstRect.x = data[1];
	dstRect.y = data[2];
	dstRect.w = data[3];
	dstRect.h = data[4];

	SDL_Rect srcRect;
	srcRect.x = data[5];
	srcRect.y = data[6];
	srcRect.w = data[7];
	srcRect.h = data[8];

	SDL_RenderCopyF((SDL_Renderer*)renderer->nativeRunderer, (SDL_Texture*)texture, &srcRect, &dstRect);
}

void EngineRenderDrawTexture(EngineRenderer* renderer, EngineRenderCommand* command){
	assert(renderer != NULL && "cannot draw from a NULL renderer");
	assert(command != NULL && "cannot draw a line from a NULL render command");
	float *data = command->data;
	
	void* texture = EngineRendererGetCurrentTextureBuffer(renderer)->content[(int)data[0]];

	SDL_FRect dstRect;
	dstRect.x = data[1];
	dstRect.y = data[2];
	dstRect.w = data[3];
	dstRect.h = data[4];

	SDL_RenderCopyF((SDL_Renderer*)renderer->nativeRunderer, (SDL_Texture*)texture, NULL, &dstRect);
}

void EngineRenderDrawRotatedSubTexture(EngineRenderer* renderer, EngineRenderCommand* command){
	assert(renderer != NULL && "cannot draw from a NULL renderer");
	assert(command != NULL && "cannot draw a line from a NULL render command");
	float *data = command->data;
	
	void* texture = EngineRendererGetCurrentTextureBuffer(renderer)->content[(int)data[0]];

	
	SDL_FRect dstRect;
	dstRect.x = data[1];
	dstRect.y = data[2];
	dstRect.w = data[3];
	dstRect.h = data[4];

	SDL_Rect srcRect;
	srcRect.x = data[5];
	srcRect.y = data[6];
	srcRect.w = data[7];
	srcRect.h = data[8];

	float angle = data[9];
	SDL_FPoint center;
	center.x = data[10];
	center.y = data[11];

	SDL_RenderCopyExF((SDL_Renderer*)renderer->nativeRunderer, (SDL_Texture*)texture, &srcRect, &dstRect, angle, &center, SDL_FLIP_NONE);
}

void EngineRenderDrawRotatedTexture(EngineRenderer* renderer, EngineRenderCommand* command){
	assert(renderer != NULL && "cannot draw from a NULL renderer");
	assert(command != NULL && "cannot draw a line from a NULL render command");
	float *data = command->data;

	SDL_FRect dstRect;
	dstRect.x = data[1];
	dstRect.y = data[2];
	dstRect.w = data[3];
	dstRect.h = data[4];
	
	float angle = data[5];
	SDL_FPoint center;
	center.x = data[6];
	center.y = data[7];

	void* texture = EngineRendererGetCurrentTextureBuffer(renderer)->content[(int)data[0]];

	SDL_RenderCopyExF((SDL_Renderer*)renderer->nativeRunderer, texture, NULL, &dstRect, angle, &center, SDL_FLIP_NONE);
}

void EngineRenderBatchDrawCalls(EngineRenderer* renderer, EngineCircularQueue* queue){
	assert(queue != NULL && "invalid queue");
	EngineRenderCommand *batchCommand = NULL;
	EngineRenderCommandType currentBatchType = ENGINE_RENDER_COMMAND_NONE;

	QueueElement* it = EngineCircularQueueGetBegin(queue);
	while (it != EngineCircularQueueGetEnd(queue)){
		EngineRenderCommand* command = it->value;

		if (!command) continue;
		
		if (command->type == currentBatchType && batchCommand){
			batchCommand->count++;
			it = it->next;
			continue;
		}

		batchCommand = command;
		EngineCircularQueuePush(renderer->batchRenderQueue, command);
		it = it->next;
	}
}

void EngineRendererDraw(EngineRenderer* renderer){
	assert(renderer != NULL && "cannot draw from a NULL renderer");
	uint8_t queueIndex = (renderer->currentQueue+1) % 2;
	EngineCircularQueue* queue = renderer->batchRenderQueue;
	EngineFloatDynamicArray* buffer = renderer->buffers[queueIndex];

	EngineRenderBatchDrawCalls(renderer, renderer->renderQueues[queueIndex]);
	
	while (!EngineCircularQueueIsEmpty(queue)){
		EngineRenderCommand* data = (EngineRenderCommand*)EngineCircularQueuePop(queue);
		if (!data || data->type == ENGINE_RENDER_COMMAND_NONE) continue;

		switch (data->type){
			case ENGINE_RENDER_COMMAND_DRAW_POINTS: EngineRenderPoints(renderer, data); break;
			case ENGINE_RENDER_COMMAND_DRAW_LINES: EngineRenderLines(renderer, data); break;
			case ENGINE_RENDER_COMMAND_DRAW_LINES_STRIP: EngineRenderLinesStrip(renderer, data); break;
			case ENGINE_RENDER_COMMAND_DRAW_RECTS: EngineRenderRects(renderer, data); break;
			case ENGINE_RENDER_COMMAND_CLEAR: EngineRenderClear(renderer, data); break;
			case ENGINE_RENDER_COMMAND_DRAW_FILLED_RECTS: EngineRenderFilledRects(renderer, data); break;
			case ENGINE_RENDER_COMMAND_SET_DRAW_COLOR: EngineRenderSetDrawColor(renderer, data); break;
			case ENGINE_RENDER_COMMAND_DRAW_SUBTEXTURE: EngineRenderDrawSubTexture(renderer, data); break;
			case ENGINE_RENDER_COMMAND_DRAW_ROTATED_SUBTEXTURE: EngineRenderDrawRotatedSubTexture(renderer, data); break;
			case ENGINE_RENDER_COMMAND_DRAW_TEXTURE: EngineRenderDrawTexture(renderer, data); break;
			case ENGINE_RENDER_COMMAND_DRAW_ROTATED_TEXTURE: EngineRenderDrawRotatedTexture(renderer, data); break;
		}
	}

	SDL_RenderPresent(renderer->nativeRunderer);
}