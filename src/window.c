// std
#include <stdio.h>
#include <assert.h>

// engine
#include "engine/window.h"

// libs
#include <libs/SDL2/SDL.h>

static uint8_t windowCount = 0;

void initializeSDL(){
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0){
		fprintf(stderr, "SDL_Init Error : %s", SDL_GetError());
		exit(EXIT_FAILURE);
	}
}

SDL_Window* createWindow(const char *title, int width, int height){
	if (windowCount == 0) initializeSDL();

	SDL_Window* window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);

	// there is no assert because this function might dosen't work on other devices
	if (!window){
		fprintf(stderr, "SDL_CreateWindow Error : %s", SDL_GetError());
		exit(EXIT_FAILURE);
	}

	windowCount++;
}

SDL_Window* destroyWindow(SDL_Window* window){
	if (window){
		SDL_DestroyWindow(window);
		windowCount--;

		if (windowCount == 0){
			SDL_Quit();
		}
	}
	return NULL;
}

EngineWindowDef* EngineWindowCreateDef(void){
	EngineWindowDef *def = malloc(sizeof(EngineWindowDef*));
	
	if (!def){
		fprintf(stderr, "alloc Error");
		exit(EXIT_FAILURE);
	}

	def->width = 1080;
	def->height = 720;
	def->title = NULL;
	def->icon = NULL;
	def->eventCallback = NULL;
	def->fullscreen = false;
	def->bordered = true;
	return def;
}

EngineWindow* EngineWindowCreate(EngineWindowDef* def){
	assert(def != NULL && "cannot create a window from a NULL definition");
	EngineWindow* window = malloc(sizeof(EngineWindow*));

	if (!window){
		fprintf(stderr, "alloc Error");
		exit(EXIT_FAILURE);
	}

	window->nativeWindow = (void*)createWindow((def->title != NULL ? def->title : "SDL Game Engine"), (int)def->width, (int)def->height);

	strcpy(window->title, SDL_GetWindowTitle(window->nativeWindow));
	window->width = def->width;
	window->height = def->height;

	window->icon = NULL;

	int x, y;
	SDL_GetWindowPosition(window->nativeWindow, &x, &y);

	window->x = x;
	window->y = y;

	EngineWindowSetOpacity(window, 1.0);
	EngineWindowSetMinimalSize(window, 0, 0);
	EngineWindowSetMaximalSize(window, (uint32_t)-1, (uint32_t)-1);
	EngineWindowSetFullscreen(window, def->fullscreen);
	EngineWindowSetEventCallback(window, def->eventCallback);

	free(def);
	return window;
}

EngineWindow* EngineWindowDestroy(EngineWindow* window){
	assert(window != NULL && "cannot destroy a NULL window");
	destroyWindow(window->nativeWindow);
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

void EngineWindowGetMaximalSize(EngineWindow* window, uint32_t* width, uint32_t* height){
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

void EngineWindowSetFullscreen(EngineWindow* window, Bool fullscreen){
	assert(window != NULL && "cannot set the fullscreen state of a NULL window");
	window->fullscreen = fullscreen;

	if (fullscreen){
		SDL_SetWindowFullscreen(window->nativeWindow, SDL_WINDOW_FULLSCREEN);
	} else {
		SDL_SetWindowFullscreen(window->nativeWindow, 0);
	}
}

void EngineWindowSetGrab(EngineWindow* window, Bool grab){
	assert(window != NULL && "cannot set the grab state of a NULL window");
	window->grab = grab;
	SDL_SetWindowGrab(window->nativeWindow, grab);
}

Bool EngineWindowIsGrabed(EngineWindow* window){
	assert(window != NULL && "cannot get the grab state of a NULL window");
	return window->grab;
}

void EngineWindowSetBordered(EngineWindow* window, Bool bordered){
	assert(window != NULL && "cannot set the bordered state of a NULL window");
	window->bordered = bordered;
	SDL_SetWindowBordered(window->nativeWindow, bordered);
}

Bool EngineWindowIsBordered(EngineWindow* window){
	assert(window != NULL && "cannot get the bordered state of a NULL window");
	return window->bordered;
}

void EngineWindowSetTitle(EngineWindow* window, const char* title){
	assert(window != NULL && "cannot set the title of a NULL window");
	if (window->title) free(window->title);
	strcpy(window->title, title);
	SDL_SetWindowTitle(window->nativeWindow, title);
}

const char* EngineWindowGetTitle(EngineWindow* window){
	assert(window != NULL && "cannot get the title of a NULL window");
	return window->title;
}

void EngineWindowMaximize(EngineWindow* window){
	assert(window != NULL && "cannot set maximize state of a NULL window");
	window->minimized = false;
	SDL_MaximizeWindow(window->nativeWindow);
}

void EngineWindowMinimize(EngineWindow* window){
	assert(window != NULL && "cannot set minimize state of a NULL window");
	window->minimized = true;
	SDL_MinimizeWindow(window->nativeWindow);
}

Bool EngineWindowIsMinimized(EngineWindow* window){
	assert(window != NULL && "cannot get minimize state of a NULL window");
	return window->minimized;
}

void EngineWindowQuitEvent(EngineWindow* window){
	assert(window != NULL && "cannot create an event with a NULL window");
	if (window->eventCallback){
		EngineEvent *event = EngineEventCreate();

		event->category = ENGINE_EVENT_CATEGORY_APPLICATION;
		event->type = ENGINE_EVENT_TYPE_WINDOW_CLOSED;
		window->eventCallback(event);

		EngineEventDestroy(event);
	}
}

void EngineWindowResizedEvent(EngineWindow* window, uint32_t width, uint32_t height){
	assert(window != NULL && "cannot create an event with a NULL window");
	if (window->eventCallback){
		EngineEvent* event = EngineEventCreate();
		EngineWindowEventResized* data = EngineWindowEventResizedCreate();

		data->width = width;
		data->height = height;
		event->category = ENGINE_EVENT_CATEGORY_APPLICATION;
		event->type = ENGINE_EVENT_TYPE_WINDOW_RESIZED;
		event->data = data;
		window->eventCallback(event);

		EngineEventDestroy(event);
	}
}

void EngineWindowMovedEvent(EngineWindow* window, uint32_t x, uint32_t y){
	assert(window != NULL && "cannot create an event with a NULL window");
	if (window->eventCallback){
		EngineEvent* event = EngineEventCreate();
		EngineWindowEventMoved* data = EngineWindowEventMovedCreate();
		
		data->x = x;
		data->y = y;
		event->category = ENGINE_EVENT_CATEGORY_APPLICATION;
		event->type = ENGINE_EVENT_TYPE_WINDOW_MOVED;
		event->data = data;
		window->eventCallback(event);

		EngineEventDestroy(event);
	}
}

void EngineWindowFocusedEvent(EngineWindow* window){
	assert(window != NULL && "cannot create an event with a NULL window");
	if (window->eventCallback){
		EngineEvent* event = EngineEventCreate();
		
		event->category = ENGINE_EVENT_CATEGORY_APPLICATION;
		event->type = ENGINE_EVENT_TYPE_WINDOW_FOCUSED;
		window->eventCallback(event);

		EngineEventDestroy(event);
	}	
}

void EngineWindowFocusLostEvent(EngineWindow* window){
	assert(window != NULL && "cannot create an event with a NULL window");
	if (window->eventCallback){
		EngineEvent* event = EngineEventCreate();

		event->category = ENGINE_EVENT_CATEGORY_APPLICATION;
		event->type = ENGINE_EVENT_TYPE_WiNDOW_LOST_FOCUS;
		window->eventCallback(event);

		EngineEventDestroy(event);
	}
}

void EngineWindowMinimizedEvent(EngineWindow* window){
	assert(window != NULL && "cannot create an event with a NULL window");
	if (window->eventCallback){
		EngineEvent* event = EngineEventCreate();

		event->category = ENGINE_EVENT_CATEGORY_APPLICATION;
		event->type = ENGINE_EVENT_TYPE_WINDOW_MINIMIZED;
		window->eventCallback(event);

		EngineEventDestroy(event);
	}
}

void EngineWindowMaximizedEvent(EngineWindow* window){
	assert(window != NULL && "cannot create an event with a NULL window");
	if (window->eventCallback){
		EngineEvent* event = EngineEventCreate();

		event->category = ENGINE_EVENT_CATEGORY_APPLICATION;
		event->type = ENGINE_EVENT_TYPE_WINDOW_MAXIMIZED;
		window->eventCallback(event);

		EngineEventDestroy(event);
	}
}


void EngineWindowUpdate(EngineWindow* window){
	assert(window != NULL && "cannot update a NULL window");

	SDL_Event e;
	while (SDL_PollEvent(&e)){
		switch (e.type){
			case SDL_QUIT: EngineWindowQuitEvent(window); break;
			case SDL_WINDOWEVENT_RESIZED: EngineWindowResizedEvent(window, (uint32_t)e.window.data1, (uint32_t)e.window.data2); break;
			case SDL_WINDOWEVENT_MOVED: EngineWindowMovedEvent(window, e.window.data1, e.window.data2); break;
			case SDL_WINDOWEVENT_FOCUS_GAINED: EngineWindowFocusedEvent(window); break;
			case SDL_WINDOWEVENT_FOCUS_LOST: EngineWindowFocusLostEvent(window); break;
			case SDL_WINDOWEVENT_MINIMIZED: EngineWindowMinimizedEvent(window); break;
			case SDL_WINDOWEVENT_MAXIMIZED: EngineWindowMaximizedEvent(window); break;

		}
	}
}

void EngineWindowSetEventCallback(EngineWindow* window, void(*callback)(EngineEvent*)){
	assert(window != NULL && "cannot set the callback of a NULL window");
	window->eventCallback = callback;
}
