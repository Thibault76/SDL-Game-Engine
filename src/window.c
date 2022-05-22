// std
#include <stdio.h>
#include <assert.h>

// engine
#include "engine/window.h"

// libs
#include <libs/SDL2/SDL.h>

SDL_Window* createWindow(const char *title, int width, int height){
	SDL_Window* window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);

	// there is no assert because this function might dosen't work on other devices
	if (!window){
		fprintf(stderr, "SDL_CreateWindow error : %s", SDL_GetError());
		exit(EXIT_FAILURE);
	}
}

EngineWindowDef* EngineWindowCreateDef(void){
	EngineWindowDef *def = malloc(sizeof(EngineWindowDef*));
	def->width = 1080;
	def->height = 720;
	def->title = NULL;
	def->icon = NULL;
	return def;
}

EngineWindow* EngineWindowCreate(EngineWindowDef* def){
	assert(def != NULL && "cannot create a window from a NULL definition");
	EngineWindow* window = malloc(sizeof(EngineWindow*));

	window->nativeWindow = (void*)createWindow((def->title != NULL ? def->title : "SDL Game Engine"), (int)def->width, (int)def->height);

	strcpy(window->title, SDL_GetWindowTitle(window->nativeWindow));
	window->width = def->width;
	window->height = def->height;

	window->icon = NULL;

	int x, y;
	SDL_GetWindowPosition(window->nativeWindow, &x, &y);

	window->x = x;
	window->y = y;

	window->opacity = 1.0;
	window->minWidth = 0;
	window->minHeight = 0;
	window->maxWidth = (uint32_t)-1;
	window->maxHeight = (uint32_t)-1;

	free(def);
	return window;
}

EngineWindow* EngineWindowDestroy(EngineWindow* window){
	assert(window != NULL && "cannot destroy a NULL window");
	free(window);
	return NULL;
}

void EngineWindowSetSize(EngineWindow* window, uint32_t width, uint32_t height){
	assert(window != NULL && "cannot set the size of a NULL window");
	window->width = width;
	window->height = height;
	SDL_SetWindowSize(window->nativeWindow, (int)width, (int)height);
}

void EngineWindowSetWidth(EngineWindow* window, uint32_t width){
	assert(window != NULL && "cannot set the width of a NULL window");
	EngineWindowSetSize(window, width, window->height);
}

void EngineWindowSetHeight(EngineWindow* window, uint32_t height){
	assert(window != NULL && "cannot set the height of a NULL window");
	EngineWindowSetSize(window, window->width, height);
}

void EngineWindowSetPosition(EngineWindow* window, uint32_t x, uint32_t y){
	assert(window != NULL && "cannot set the position of a NULL window");
	window->x = x;
	window->y = y;
	SDL_SetWindowPosition(window->nativeWindow, (int)x, (int)y);
}

void EngineWindowSetPositionX(EngineWindow* window, uint32_t x){
	assert(window != NULL && "cannot set the position of a NULL window");
	EngineWindowSetPosition(window, x, window->y);
}

void EngineWindowSetPositionY(EngineWindow* window, uint32_t y){
	assert(window != NULL && "cannot set the position of a NULL window");
	EngineWindowSetPosition(window, window->x, y);
}

void EngineWindowSetPositionCenter(EngineWindow* window){
	assert(window != NULL && "cannot set the position of a NULL window");
	SDL_SetWindowPosition(window->nativeWindow, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
	int x, y;
	SDL_GetWindowPosition(window->nativeWindow, &x, &y);
	window->x = x;
	window->y = y;
}

void EngineWindowGetSize(EngineWindow* window, uint32_t* width, uint32_t* height){
	assert(window != NULL && "cannot get the size of a NULL window");
	if (width) *width = window->width;
	if (height) *height = window->height;
}

uint32_t EngineWindowGetWidth(EngineWindow* window){
	assert(window != NULL && "cannot get the size of a NULL window");
	return window->width;
}

uint32_t EngineWindowGetHeight(EngineWindow* window){
	assert(window != NULL && "cannot get the size of a NULL window");
	return window->height;
}

void EngineWindowGetPosition(EngineWindow* window, uint32_t* x, uint32_t* y){
	assert(window != NULL && "cannot get the position of a NULL window");
	if (x) *x = window->x;
	if (y) *y = window->y;
}

uint32_t EngineWindowGetPositionX(EngineWindow* window){
	assert(window != NULL && "cannot get the position of a NULL window");
	return window->x;
}

uint32_t EngineWindowGetPositionY(EngineWindow* window){
	assert(window != NULL && "cannot get the position of a NULL window");
	return window->y;
}

void EngineWindowSetMinimalSize(EngineWindow* window, uint32_t width, uint32_t height){
	assert(window != NULL && "cannot set the minimal size of a NULL window");
	window->minWidth = width;
	window->minHeight = height;
	SDL_SetWindowMinimumSize(window->nativeWindow, (int)width, (int)height);
}

void EngineWindowSetMaximalSize(EngineWindow* window, uint32_t width, uint32_t height){
	assert(window != NULL && "cannot set the maximal size of a NULL window");
	window->maxWidth = width;
	window->maxHeight = height;
	SDL_SetWindowMaximumSize(window->nativeWindow, (int)width, (int)height);
}

void EngineWindowGetMinimalSize(EngineWindow* window, uint32_t* width, uint32_t* height){
	assert(window != NULL && "cannot get the minimal size of a NULL window");
	if (width) *width = window->minWidth;
	if (height) *height = window->minHeight;
}

void EngineWindowGetMinimalSize(EngineWindow* window, uint32_t* width, uint32_t* height){
	assert(window != NULL && "cannot get the maximal size of a NULL window");
	if (width) *width = window->maxWidth;
	if (height) *height = window->maxHeight;
}

void EngineWindowSetOpacity(EngineWindow* window, float opacity){
	assert(window != NULL && "cannot set the opacity of a NULL window");
	window->opacity = opacity;
	SDL_SetWindowOpacity(window->nativeWindow, opacity);
}

float EngineWindowGetOpacity(EngineWindow* window){
	assert(window != NULL && "cannot get the opacity of a NULL window");
	return window->opacity;
}
