#pragma once

#include "core.h"

typedef struct{
	uint32_t width;
	uint32_t height;
	uint32_t minWidth;
	uint32_t minHeight;
	uint32_t maxWidth;
	uint32_t maxHeight;

	uint32_t x;
	uint32_t y;
	char* title;
	void* icon;
	float opacity;
	Bool fullscreen;
	Bool grab;
	Bool bordered;
	Bool minimized;

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
	Bool fullscreen;
	Bool bordered;

} EngineWindowDef;

/**
 * @brief initialize a new Window definition with basics parameters
 * @return EngineWindowDef* 
 */
EngineWindowDef* EngineWindowCreateDef(void);

/**
 * @brief create a window with from the given definition
 * 
 * @param def the pointer to the window definition /!\ get implicitly destroyed once the window is created /!\
 * @return EngineWindow* 
 */
EngineWindow* EngineWindowCreate(EngineWindowDef* def);

/**
 * @brief close and destroy from the memory the given window
 * @param window the window to destroy
 * @return EngineWindow* 
 */
EngineWindow* EngineWindowDestroy(EngineWindow* window);

/**
 * @brief set the size of the given window
 * @param window the window to resize
 * @param width the new width of the window in pixels
 * @param height the new height of the window in pixels
 */
void EngineWindowSetSize(EngineWindow* window, uint32_t width, uint32_t height);

/**
 * @brief set the width of the given window
 * @param window the window to resize
 * @param width the new width of the window in pixels
 */
void EngineWindowSetWidth(EngineWindow* window, uint32_t width);

/**
 * @brief set the width of the given window
 * @param window the window to resize
 * @param height the new height of the window in pixels
 */
void EngineWindowSetHeight(EngineWindow* window, uint32_t height);

/**
 * @brief set the position on pixels of the top left corner of the window
 * @param window the window to move
 * @param x the x axis in pixels of the window
 * @param y the y axis in pixels of the window
 */
void EngineWindowSetPosition(EngineWindow* window, uint32_t x, uint32_t y);

/**
 * @brief set the position on pixels of the top left corner of the window
 * @param window the window to move
 * @param x the x axis in pixels of the window
 */
void EngineWindowSetPositionX(EngineWindow* window, uint32_t x);

/**
 * @brief set the position on pixels of the top left corner of the window
 * @param window the window to move
 * @param y the y axis in pixels of the window
 */
void EngineWindowSetPositionY(EngineWindow* window, uint32_t y);

/**
 * @brief move the window to the center of the monitor
 * @param window the window to move
 */
void EngineWindowSetPositionCenter(EngineWindow* window);

/**
 * @brief retrive the size of the window
 * @param window
 * @param width the pointer to the width destination, can be NULL 
 * @param height the pointer to the height destination, can be NULL
 */
void EngineWindowGetSize(EngineWindow* window, uint32_t* width, uint32_t* height);

/**
 * @brief get the width of the given window
 * @return uint32_t 
 */
uint32_t EngineWindowGetWidth(EngineWindow* window);

/**
 * @brief get the height of the given window
 * @return uint32_t 
 */
uint32_t EngineWindowGetHeight(EngineWindow* window);

/**
 * @brief get the position of the top left corner of the window, in pixels
 * @param x the pointer to the X destination, can be NULL
 * @param y the pointer to the Y destination, can be NULL
 */
void EngineWindowGetPosition(EngineWindow* window, uint32_t* x, uint32_t* y);

/**
 * @brief get the X position of the top left corner of the window, in pixels
 * @return uint32_t 
 */
uint32_t EngineWindowGetPositionX(EngineWindow* window);

/**
 * @brief get the X position of the top left corner of the window, in pixels
 * @return uint32_t 
 */
uint32_t EngineWindowGetPositionY(EngineWindow* window);

/**
 * @brief set the minimal size of the window
 * @param width the miniaml width in pixels
 * @param height the minimal height in pixels
 */
void EngineWindowSetMinimalSize(EngineWindow* window, uint32_t width, uint32_t height);

/**
 * @brief set the maximal size of the window
 * @param width the maximal width in pixels
 * @param height the maximal height in pixels
 */
void EngineWindowSetMaximalSize(EngineWindow* window, uint32_t width, uint32_t height);

/**
 * @brief get the minimal size of the window, in pixels
 * @param width the pointer to the width destination, can be NULL
 * @param height the pointer to the height destination, can be NULL
 */
void EngineWindowGetMinimalSize(EngineWindow* window, uint32_t* width, uint32_t* height);

/**
 * @brief get the maximal size of the window, in pixels
 * @param width the pointer to the width destination, can be NULL
 * @param height the pointer to the height destination, can be NULL
 */
void EngineWindowGetMaximalSize(EngineWindow* window, uint32_t* width, uint32_t* height);

/**
 * @brief set the opacity of the window in range from 0.0 to 1.0
 * @param opacity the opacity in range from 0.0 to 1.0 
 */
void EngineWindowSetOpacity(EngineWindow* window, float opacity);

/**
 * @brief get the opacity of the window
 * @param window the window
 * @return float 
 */
float EngineWindowGetOpacity(EngineWindow* window);

/**
 * @brief set the window to fullscreen mode
 * @param fullscreen if fullscreen
 */
void EngineWindowSetFullscreen(EngineWindow* window, Bool fullscreen);

/**
 * @brief grab the window with the mouse
 */
void EngineWindowSetGrab(EngineWindow* window, Bool grab);

/**
 * @brief get if the window is currently grabed
 * @param window the window to check
 */
Bool EngineWindowIsGrabed(EngineWindow* window);

/**
 * @brief set if the window is bordered
 * @param window the window to set
 * @param bordered 
 */
void EngineWindowSetBordered(EngineWindow* window, Bool bordered);

/**
 * @brief get if the window is bordered
 * @param window the window to check
 */
void EngineWindowIsBordered(EngineWindow* window);

/**
 * @brief set the title of the window
 * @param title the new title of the window
 */
void EngineWindowSetTitle(EngineWindow* window, const char* title);

/**
 * @brief get the title of the given window
 * @return const char* 
 */
const char* EngineWindowGetTitle(EngineWindow* window);

/**
 * @brief maximize the window
 * @param window the window to maximize
 */
void EngineWindowMaximize(EngineWindow* window);

/**
 * @brief minimize the window
 * @param window the window to minimize
 */
void EngineWindowMinimize(EngineWindow* window);

/**
 * @brief check if the given window is minimized
 * @param window 
 */
void EngineWindowIsMinimized(EngineWindow* window);