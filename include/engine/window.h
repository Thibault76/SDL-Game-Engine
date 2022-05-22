#pragma once

#include "core.h"

typedef struct{
	uint32_t width;
	uint32_t height;
	char* title;

	void* nativeWindow; // the pointer to the SDL_Window
} EngineWindow;


/**
 * @brief the window initialization parameters
 * 
 */
typedef struct{
	uint32_t width;
	uint32_t height;
	char* title;
	void* icon;

} EngineWindowDef;

/**
 * @brief initialize a new Window definition with basics parameters
 * @return EngineWindowDef* 
 */
EngineWindowDef* EngineCreateWindowDef();

/**
 * @brief create a window with from the given definition
 * 
 * @param def the pointer to the window definition /!\ get implicitly destroyed once the window is created /!\
 * @return EngineWindow* 
 */
EngineWindow* EngineCreateWindow(EngineWindowDef* def);

/**
 * @brief close and destroy from the memory the given window
 * @param window the window to destroy
 * @return EngineWindow* 
 */
EngineWindow* EngineDestroyWindow(EngineWindow* window);