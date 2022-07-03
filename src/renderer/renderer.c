#include "engine/renderer/renderer.h"
#include "engine/window.h"
#include <assert.h>
#include <libs/SDL2/SDL.h>

EngineRenderCommand* EngineRendererPushCommand(EngineRenderer *renderer){
	assert(renderer != NULL && "push command into a NULL renderer");
	EngineRenderCommand *queue = renderer->renderQueues[renderer->currentQueue];

	if (renderer->commandCounts[renderer->currentQueue]+1 >= renderer->allocatedCommandCount[renderer->currentQueue]){
		const int step = 150;

		renderer->allocatedCommandCount[renderer->currentQueue] += step;
		queue = realloc(queue, sizeof(EngineRenderCommand) * renderer->allocatedCommandCount[renderer->currentQueue]);
		MALLOC_CHECK(queue);

		for (int i=renderer->commandCounts[renderer->currentQueue]; i<renderer->allocatedCommandCount[renderer->currentQueue]; i++){
			// printf("%d\n", i);
			queue[i].dataIndex = 0;
			queue[i].count = 1;
			queue[i].type = ENGINE_RENDER_COMMAND_NONE;
		}
	}

	EngineRenderCommand *command = &renderer->renderQueues[renderer->currentQueue][renderer->commandCounts[renderer->currentQueue]++];
	command->dataIndex = 0;
	command->count = 1;
	command->type = ENGINE_RENDER_COMMAND_NONE;
	
	return command;
}

uint32_t EngineRendererBufferInsert(EngineRenderer *renderer, float data){
	assert(renderer != NULL && "push data into a NULL renderer");
	
	if (renderer->buffersSize[renderer->currentQueue]+1 >= renderer->buffersAllocatedSize[renderer->currentQueue]){
		renderer->buffersAllocatedSize[renderer->currentQueue] += 150;
		renderer->buffers[renderer->currentQueue] = realloc(renderer->buffers[renderer->currentQueue], sizeof(float) * renderer->buffersAllocatedSize[renderer->currentQueue]);
		MALLOC_CHECK(renderer->buffers[renderer->currentQueue]);
	}

	renderer->buffers[renderer->currentQueue][renderer->buffersSize[renderer->currentQueue]] = data;
	uint32_t tempSize = renderer->buffersSize[renderer->currentQueue];
	renderer->buffersSize[renderer->currentQueue]++;
	return tempSize;
}

uint32_t EngineRendererTextureBufferInsert(EngineRenderer *renderer, void* data){
	assert(renderer != NULL && "push data into a NULL renderer");
	if (renderer->textureBuffersSize[renderer->currentQueue]+1 >= renderer->textureBuffersAllocatedSize[renderer->currentQueue]){
		renderer->textureBuffersAllocatedSize[renderer->currentQueue] += 150;
		renderer->textureBuffers[renderer->currentQueue] = realloc(renderer->textureBuffers[renderer->currentQueue], sizeof(void*) * renderer->textureBuffersAllocatedSize[renderer->currentQueue]);
		MALLOC_CHECK(renderer->textureBuffers[renderer->currentQueue]);
	}

	renderer->textureBuffers[renderer->currentQueue][renderer->textureBuffersSize[renderer->currentQueue]] = data;
	uint32_t tempSize = renderer->textureBuffersSize[renderer->currentQueue];
	renderer->textureBuffersSize[renderer->currentQueue]++;
	return tempSize;
}

EngineRenderer* EngineRendererCreate(EngineWindow* window, uint32_t renderCommandCount){
	EngineRenderer* renderer = malloc(sizeof(EngineRenderer));
	MALLOC_CHECK(renderer);

	renderer->window = window;

	for (uint8_t queue=0; queue<2; queue++){
		renderer->renderQueues[queue] = malloc(sizeof(EngineRenderCommand) * renderCommandCount);
		renderer->allocatedCommandCount[queue] = renderCommandCount;
		renderer->commandCounts[queue] = 0;
		MALLOC_CHECK(renderer->renderQueues[queue]);

		for (int i=0; i<renderCommandCount; i++){
			EngineRenderCommand* command = &renderer->renderQueues[queue][i];
			command->count = 1;
			command->dataIndex = 0;
			command->type = ENGINE_RENDER_COMMAND_NONE;
		}

		renderer->buffers[queue] = malloc(sizeof(float) * renderCommandCount);
		renderer->buffersAllocatedSize[queue] = renderCommandCount;
		renderer->buffersSize[queue] = 0;
		MALLOC_CHECK(renderer->buffers[queue]);
		renderer->textureBuffers[queue] = malloc(sizeof(void*) * renderCommandCount);
		renderer->textureBuffersAllocatedSize[queue] = renderCommandCount;
		renderer->textureBuffersSize[queue] = 0;
		MALLOC_CHECK(renderer->textureBuffers[queue]);
	}
	renderer->currentQueue = 0;
	renderer->batchRenderQueueAllocatedCommmandCount = renderCommandCount;
	renderer->batchRenderQueueCommandCount = 0;
	renderer->batchRenderQueue = malloc(sizeof(EngineRenderCommand*) * renderCommandCount);
	MALLOC_CHECK(renderer->batchRenderQueue);

	renderer->nativeRunderer = SDL_CreateRenderer(window->nativeWindow, -1, 0);
	if (renderer->nativeRunderer == NULL){
		fprintf(stderr, "SDL_CreateRenderer Error : %s", SDL_GetError());
		exit(EXIT_FAILURE);
	}

	return renderer;
}

void EngineRendererDestroy(EngineRenderer* renderer){
	assert(renderer != NULL && "cannot destroy a NULL renderer");

	for (uint8_t queue=0; queue<2; queue++){
		free(renderer->renderQueues[queue]);
		free(renderer->buffers[queue]);
		free(renderer->textureBuffers[queue]);
	}

	free(renderer->batchRenderQueue);
	SDL_DestroyRenderer(renderer->nativeRunderer);
	free(renderer);
	renderer = NULL;
}

void EngineRendererClear(EngineRenderer* renderer){
	assert(renderer != NULL && "cannot draw on a NULL renderer");
	EngineRenderCommand* command = EngineRendererPushCommand(renderer);
	command->type = ENGINE_RENDER_COMMAND_CLEAR;
}

void EngineRendererSetDrawColor(EngineRenderer* renderer, uint8_t r, uint8_t g, uint8_t b, uint8_t a){
	assert(renderer != NULL && "cannot draw on a NULL renderer");
	EngineRenderCommand* command = EngineRendererPushCommand(renderer);
	command->count = 1;
	command->type = ENGINE_RENDER_COMMAND_SET_DRAW_COLOR;
	command->dataIndex = EngineRendererBufferInsert(renderer, (float)r);
	EngineRendererBufferInsert(renderer, (float)g);
	EngineRendererBufferInsert(renderer, (float)b);
	EngineRendererBufferInsert(renderer, (float)a);
}

void EngineRendererDrawPoint(EngineRenderer* renderer, float x, float y){
	assert(renderer != NULL && "cannot draw on a NULL renderer");
	EngineRenderCommand* command = EngineRendererPushCommand(renderer);
	command->count = 1;
	command->type = ENGINE_RENDER_COMMAND_DRAW_POINTS;
	command->dataIndex = EngineRendererBufferInsert(renderer, x);
	EngineRendererBufferInsert(renderer, y);
}

void EngineRendererDrawLine(EngineRenderer* renderer, float x1, float y1, float x2, float y2){
	assert(renderer != NULL && "cannot draw on a NULL renderer");
	EngineRenderCommand* command = EngineRendererPushCommand(renderer);
	command->type = ENGINE_RENDER_COMMAND_DRAW_LINES;
	command->dataIndex = EngineRendererBufferInsert(renderer, x1);
	EngineRendererBufferInsert(renderer, y1);
	EngineRendererBufferInsert(renderer, x2);
	EngineRendererBufferInsert(renderer, y2);
}

void EngineRendererDrawLineStrip(EngineRenderer* renderer, float x1, float y1, float x2, float y2){
	assert(renderer != NULL && "cannot draw on a NULL renderer");
	EngineRenderCommand* command = EngineRendererPushCommand(renderer);
	command->type = ENGINE_RENDER_COMMAND_DRAW_LINES_STRIP;
	command->dataIndex = EngineRendererBufferInsert(renderer, x1);
	EngineRendererBufferInsert(renderer, y1);
	EngineRendererBufferInsert(renderer, x2);
	EngineRendererBufferInsert(renderer, y2);
}

void EngineRendererDrawRect(EngineRenderer* renderer, float x, float y, float width, float height){
	assert(renderer != NULL && "cannot draw on a NULL renderer");
	EngineRenderCommand* command = EngineRendererPushCommand(renderer);
	command->type = ENGINE_RENDER_COMMAND_DRAW_RECTS;
	command->dataIndex = EngineRendererBufferInsert(renderer, x);
	EngineRendererBufferInsert(renderer, y);
	EngineRendererBufferInsert(renderer, width);
	EngineRendererBufferInsert(renderer, height);
}

void EngineRendererDrawFilledRect(EngineRenderer* renderer, float x, float y, float width, float height){
	assert(renderer != NULL && "cannot draw on a NULL renderer");
	EngineRenderCommand* command = EngineRendererPushCommand(renderer);
	command->type = ENGINE_RENDER_COMMAND_DRAW_FILLED_RECTS;
	command->dataIndex = EngineRendererBufferInsert(renderer, x);
	EngineRendererBufferInsert(renderer, y);
	EngineRendererBufferInsert(renderer, width);
	EngineRendererBufferInsert(renderer, height);
}

void EngineRendererDrawSubTexture(EngineRenderer* renderer, float x, float y, float width, float height, EngineSubTexture* texture){
	assert(renderer != NULL && "cannot draw on a NULL renderer");
	EngineRenderCommand* command = EngineRendererPushCommand(renderer);
	command->type = ENGINE_RENDER_COMMAND_DRAW_SUBTEXTURE;
	command->dataIndex = EngineRendererBufferInsert(renderer, renderer->textureBuffersSize[renderer->currentQueue]);
	EngineRendererTextureBufferInsert(renderer, texture->texture);
	EngineRendererBufferInsert(renderer, x);
	EngineRendererBufferInsert(renderer, y);
	EngineRendererBufferInsert(renderer, width);
	EngineRendererBufferInsert(renderer, height);
	EngineRendererBufferInsert(renderer, (float)texture->x);
	EngineRendererBufferInsert(renderer, (float)texture->y);
	EngineRendererBufferInsert(renderer, (float)texture->w);
	EngineRendererBufferInsert(renderer, (float)texture->h);
}

void EngineRendererDrawRotatedSubTexture(EngineRenderer* renderer, float x, float y, float width, float height, float angle, float rotationX, float rotationY,  EngineSubTexture* texture){
	assert(renderer != NULL && "cannot draw on a NULL renderer");
	EngineRenderCommand* command = EngineRendererPushCommand(renderer);
	command->count = 1;
	command->type = ENGINE_RENDER_COMMAND_DRAW_ROTATED_SUBTEXTURE;
	command->dataIndex = EngineRendererBufferInsert(renderer, renderer->textureBuffersSize[renderer->currentQueue]);
	EngineRendererTextureBufferInsert(renderer, texture->texture);
	EngineRendererBufferInsert(renderer, x);
	EngineRendererBufferInsert(renderer, y);
	EngineRendererBufferInsert(renderer, width);
	EngineRendererBufferInsert(renderer, height);
	EngineRendererBufferInsert(renderer, (float)texture->x);
	EngineRendererBufferInsert(renderer, (float)texture->y);
	EngineRendererBufferInsert(renderer, (float)texture->w);
	EngineRendererBufferInsert(renderer, (float)texture->h);
	EngineRendererBufferInsert(renderer, angle);
	EngineRendererBufferInsert(renderer, rotationX);
	EngineRendererBufferInsert(renderer, rotationY);
}

void EngineRendererDrawTexture(EngineRenderer* renderer, float x, float y, float width, float height, EngineTexture* texture){
	assert(renderer != NULL && "cannot draw on a NULL renderer");
	EngineRenderCommand* command = EngineRendererPushCommand(renderer);
	command->count = 1;
	command->type = ENGINE_RENDER_COMMAND_DRAW_TEXTURE;
	command->dataIndex = EngineRendererBufferInsert(renderer, renderer->textureBuffersSize[renderer->currentQueue]);
	EngineRendererTextureBufferInsert(renderer, texture->texture);
	EngineRendererBufferInsert(renderer, x);
	EngineRendererBufferInsert(renderer, y);
	EngineRendererBufferInsert(renderer, width);
	EngineRendererBufferInsert(renderer, height);
}

void EngineRendererDrawRotatedTexture(EngineRenderer* renderer, float x, float y, float width, float height, float angle, float rotationX, float rotationY, EngineTexture* texture){
	assert(renderer != NULL && "cannot draw on a NULL renderer");
	EngineRenderCommand* command = EngineRendererPushCommand(renderer);
	command->count = 1;
	command->type = ENGINE_RENDER_COMMAND_DRAW_ROTATED_TEXTURE;
	command->dataIndex = EngineRendererBufferInsert(renderer, renderer->textureBuffersSize[renderer->currentQueue]);
	EngineRendererTextureBufferInsert(renderer, texture->texture);
	EngineRendererBufferInsert(renderer, x);
	EngineRendererBufferInsert(renderer, y);
	EngineRendererBufferInsert(renderer, width);
	EngineRendererBufferInsert(renderer, height);
	EngineRendererBufferInsert(renderer, angle);
	EngineRendererBufferInsert(renderer, rotationX);
	EngineRendererBufferInsert(renderer, rotationY);
}

EngineRenderCommand* EngineRendererGetCurrentQueue(EngineRenderer* renderer){
	assert(renderer != NULL && "cannot get the current queue of a NULL renderer");
	return renderer->renderQueues[renderer->currentQueue];
}

void** EngineRendererGetCurrentTextureBuffer(EngineRenderer* renderer){
	assert(renderer != NULL && "cannot get the current buffer of a NULL renderer");	
	return renderer->textureBuffers[renderer->currentQueue];
}

void EngineRendererSwap(EngineRenderer* renderer){
	assert(renderer != NULL && "cannot swap a NULL renderer");
	renderer->currentQueue = (renderer->currentQueue+1) % 2;

	renderer->buffersSize[renderer->currentQueue] = 0;
	renderer->commandCounts[renderer->currentQueue] = 0;
	renderer->batchRenderQueueCommandCount = 0;
}

void EngineRenderPoints(EngineRenderer* renderer, EngineRenderCommand* command){
	assert(renderer != NULL && "cannot draw from a NULL renderer");
	assert(command != NULL && "cannot draw a line from a NULL render command");
	SDL_RenderDrawPointsF(renderer->nativeRunderer, (SDL_FPoint*)&renderer->buffers[renderer->currentQueue][command->dataIndex], (int)command->count);
}

void EngineRenderLinesStrip(EngineRenderer* renderer, EngineRenderCommand* command){
	assert(renderer != NULL && "cannot draw from a NULL renderer");
	assert(command != NULL && "cannot draw a line from a NULL render command");
	SDL_RenderDrawLinesF(renderer->nativeRunderer, (const SDL_FPoint*)&renderer->buffers[renderer->currentQueue][command->dataIndex], command->count*2);
}

void EngineRenderLines(EngineRenderer* renderer, EngineRenderCommand* command){
	assert(renderer != NULL && "cannot draw from a NULL renderer");
	assert(command != NULL && "cannot draw a line from a NULL render command");

	for (uint16_t i=0; i<command->count; i++){
		float* data = &renderer->buffers[renderer->currentQueue][command->dataIndex];
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
	// const SDL_Rect *rects = 
	SDL_RenderDrawRectsF(renderer->nativeRunderer, (SDL_FRect*)&renderer->buffers[renderer->currentQueue][command->dataIndex], command->count);
}

void EngineRenderFilledRects(EngineRenderer* renderer, EngineRenderCommand* command){
	assert(renderer != NULL && "cannot draw from a NULL renderer");
	assert(command != NULL && "cannot draw a line from a NULL render command");
	SDL_RenderFillRectsF(renderer->nativeRunderer, (SDL_FRect*)&renderer->buffers[renderer->currentQueue][command->dataIndex], command->count);
}

void EngineRenderClear(EngineRenderer* renderer, EngineRenderCommand* command){
	assert(renderer != NULL && "cannot draw from a NULL renderer");
	assert(command != NULL && "cannot draw a line from a NULL render command");
	SDL_RenderClear(renderer->nativeRunderer);
}

void EngineRenderSetDrawColor(EngineRenderer* renderer, EngineRenderCommand* command){
	assert(renderer != NULL && "cannot draw from a NULL renderer");
	assert(command != NULL && "cannot draw a line from a NULL render command");
	
	float *color = &renderer->buffers[renderer->currentQueue][command->dataIndex];
	uint8_t r = color[0];
	uint8_t g = color[1];
	uint8_t b = color[2];
	uint8_t a = color[3];
	SDL_SetRenderDrawColor(renderer->nativeRunderer, r, g, b, a);
}

void EngineRenderDrawSubTexture(EngineRenderer* renderer, EngineRenderCommand* command){
	assert(renderer != NULL && "cannot draw from a NULL renderer");
	assert(command != NULL && "cannot draw a line from a NULL render command");
	float *data = &renderer->buffers[renderer->currentQueue][command->dataIndex];

	void* texture = EngineRendererGetCurrentTextureBuffer(renderer)[(int)data[0]];

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
	float *data = &renderer->buffers[renderer->currentQueue][command->dataIndex];
	
	void* texture = EngineRendererGetCurrentTextureBuffer(renderer)[(int)data[0]];

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
	float *data = &renderer->buffers[renderer->currentQueue][command->dataIndex];
	
	void* texture = EngineRendererGetCurrentTextureBuffer(renderer)[(int)data[0]];

	
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
	float *data = &renderer->buffers[renderer->currentQueue][command->dataIndex];

	SDL_FRect dstRect;
	dstRect.x = data[1];
	dstRect.y = data[2];
	dstRect.w = data[3];
	dstRect.h = data[4];
	
	float angle = data[5];
	SDL_FPoint center;
	center.x = data[6];
	center.y = data[7];

	void* texture = EngineRendererGetCurrentTextureBuffer(renderer)[(int)data[0]];

	SDL_RenderCopyExF((SDL_Renderer*)renderer->nativeRunderer, texture, NULL, &dstRect, angle, &center, SDL_FLIP_NONE);
}

void EngineRenderBatchDrawCalls(EngineRenderer* renderer, EngineRenderCommand* queue){
// 	assert(queue != NULL && "invalid queue");
// 	EngineRenderCommand *batchCommand = NULL;
// 	EngineRenderCommandType currentBatchType = ENGINE_RENDER_COMMAND_NONE;

// 	const int max = renderer->commandCounts[renderer->currentQueue];
// 	for (int i=0; i<max; i++){
// 		EngineRenderCommand *command = &queue[i];

// 		if (command->type == currentBatchType && batchCommand){
// 			batchCommand->count++;
// 			continue;
// 		}

// 		batchCommand = command;
// 	}

// 	QueueElement* it = EngineCircularQueueGetBegin(queue);
// 	while (it != EngineCircularQueueGetEnd(queue)){
// 		EngineRenderCommand* command = it->value;

// 		if (!command) continue;
		
		

// 		batchCommand = command;
// 		EngineCircularQueuePush(renderer->batchRenderQueue, command);
// 		it = it->next;
// 	}
}

void EngineRendererDraw(EngineRenderer* renderer){
	assert(renderer != NULL && "cannot draw from a NULL renderer");
	uint8_t queueIndex = (renderer->currentQueue+1) % 2;

	for (int i=0; i<renderer->commandCounts[queueIndex]; i++){
		EngineRenderCommand* data = &renderer->renderQueues[queueIndex][i];
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