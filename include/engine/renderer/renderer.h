#pragma once

#include "../core.h"
#include "../window.h"
#include "../dataStructure/circularQueue.h"
#include "../dataStructure/floatDynamicArray.h"
#include "../dataStructure/dynamicArray.h"
#include "subTexture.h"
#include "texture.h"
#include "renderCommand.h"

typedef struct{
	EngineRenderCommand* renderQueues[2]; // an array of render commands
	uint32_t commandCounts[2];
	uint32_t allocatedCommandCount[2];
	uint8_t currentQueue;

	float* buffers[2];
	uint32_t buffersSize[2];
	uint32_t buffersAllocatedSize[2];

	void** textureBuffers[2];
	uint32_t textureBuffersSize[2];
	uint32_t textureBuffersAllocatedSize[2];

	EngineRenderCommand** batchRenderQueue;
	uint32_t batchRenderQueueCommandCount;
	uint32_t batchRenderQueueAllocatedCommmandCount;

	void* nativeRunderer;
	EngineWindow* window;
} EngineRenderer;

/**
 * @brief create and initialize a renderer
 * @param renderCommandCount 
 * @return EngineRenderer* 
 */
EngineRenderer* EngineRendererCreate(EngineWindow* window, uint32_t renderCommandCount);

/**
 * @brief clear and destroy the given renderer from memory
 * @param renderer 
 */
void EngineRendererDestroy(EngineRenderer* renderer);

/**
 * @brief clear the renderer and fill it with the draw color
 * @param renderer 
 */
void EngineRendererClear(EngineRenderer* renderer);

/**
 * @brief set the draw color for the next render draw calls
 * 
 * @param renderer the renderer to set
 * @param r the red channel [0, 255]
 * @param g the green channel [0, 255]
 * @param b the blue channel [0, 255]
 * @param a the alpha channel [0, 255]
 */
void EngineRendererSetDrawColor(EngineRenderer* renderer, uint8_t r, uint8_t g, uint8_t b, uint8_t a);

/**
 * @brief draw a point of one pixel by one pixel at the given coords
 * 
 * @param renderer the renderer to draw on
 * @param x the x axis in pixels of the point
 * @param y the y axis in pixels of the point
 */
void EngineRendererDrawPoint(EngineRenderer* renderer, float x, float y);

/**
 * @brief draw a straight line from [x1, y1] to [x2, y2]
 * 
 * @param renderer the renderer to draw an
 * @param x1 the x axis of the start coords
 * @param y1 the y axis of the start coords
 * @param x2 the x axis of the end coords
 * @param y2 the y axis of the end coords
 */
void EngineRendererDrawLine(EngineRenderer* renderer, float x1, float y1, float x2, float y2);

/**
 * @brief draw lines connected together
 * 
 * @param renderer the renderer to draw on
 * @param x1 the x axis of the start coords
 * @param y1 the y axis of the start coords
 * @param x2 the x axis of the end coords
 * @param y2 the y axis of the end coords
 */
void EngineRendererDrawLineStrip(EngineRenderer* renderer, float x1, float y1, float x2, float y2);

/**
 * @brief draw an empty rectangle on the renderer
 * 
 * @param renderer the renderer to draw on
 * @param x the x axis of the top left corner
 * @param y the y axis of the top left corner
 * @param width the width of the rectangle in pixels
 * @param height the height of the rectangle in pixels
 */
void EngineRendererDrawRect(EngineRenderer* renderer, float x, float y, float width, float height);

/**
 * @brief draw a filled rectangle on the renderer
 * 
 * @param renderer the renderer to draw on
 * @param x the x axis of the top left corner
 * @param y the y axis of the top left corner
 * @param width the width of the rectangle in pixels
 * @param height the height of the rectangle in pixels
 */
void EngineRendererDrawFilledRect(EngineRenderer* renderer, float x, float y, float width, float height);

/**
 * @brief draw a sub texture onto the renderer
 * 
 * @param renderer the renderer to draw on
 * @param x the x axis of the top left corner of the texture
 * @param y the y axis of the top left corner of the texture
 * @param width the width in pixels of the texture
 * @param height the height in pixexls of the texture
 * @param texture the texture to draw
 */
void EngineRendererDrawSubTexture(EngineRenderer* renderer, float x, float y, float width, float height, EngineSubTexture* texture);

/**
 * @brief draw a sub texture onto the renderer
 * 
 * @param renderer the renderer to draw on
 * @param x the x axis of the top left corner of the texture
 * @param y the y axis of the top left corner of the texture
 * @param width the width in pixels of the texture
 * @param height the height in pixexls of the texture
 * @param angle the angle of rotation in degrees
 * @param rotationX the x axis of the rotation center
 * @param rotationY the y axis of the rotation center
 * @param texture the texture to draw
 */
void EngineRendererDrawRotatedSubTexture(EngineRenderer* renderer, float x, float y, float width, float height, float angle, float rotationX, float rotationY,  EngineSubTexture* texture);

/**
 * @brief draw a sub texture onto the renderer
 * 
 * @param renderer the renderer to draw on
 * @param x the x axis of the top left corner of the texture
 * @param y the y axis of the top left corner of the texture
 * @param width the width in pixels of the texture
 * @param height the height in pixexls of the texture
 * @param texture the texture to draw
 */
void EngineRendererDrawTexture(EngineRenderer* renderer, float x, float y, float width, float height, EngineTexture* texture);

/**
 * @brief draw a sub texture onto the renderer
 * 
 * @param renderer the renderer to draw on
 * @param x the x axis of the top left corner of the texture
 * @param y the y axis of the top left corner of the texture
 * @param width the width in pixels of the texture
 * @param height the height in pixexls of the texture
 * @param angle the angle of rotation in degrees
 * @param rotationX the x axis of the rotation center
 * @param rotationY the y axis of the rotation center
 * @param texture the texture to draw
 */
void EngineRendererDrawRotatedTexture(EngineRenderer* renderer, float x, float y, float width, float height, float angle, float rotationX, float rotationY, EngineTexture* texture);

/**
 * @brief get the current queue of the renderer
 * @param renderer 
 * @return EngineCircularQueue* 
 */
EngineRenderCommand* EngineRendererGetCurrentQueue(EngineRenderer* renderer);

/**
 * @brief get the current texture buffer of the renderer
 * @param renderer 
 * @return void** 
 */
void** EngineRendererGetCurrentTextureBuffer(EngineRenderer* renderer);

/**
 * @brief swap the renderer queue and data buffer
 * @param renderer 
 */
void EngineRendererSwap(EngineRenderer* renderer);

/**
 * @brief draw the non-current queue onto the screen
 * @param renderer 
 */
void EngineRendererDraw(EngineRenderer* renderer);