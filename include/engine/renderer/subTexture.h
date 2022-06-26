#pragma once

#include "../core.h"
#include "texture.h"

typedef struct{
	EngineTexture* texture;
	uint32_t x, y;
	uint32_t w, h;
	// TODO #20
} EngineSubTexture;

/**
 * @brief create and initialize a sub texture
 * @param texture 
 * @return EngineSubTexture* 
 */
EngineSubTexture* EngineSubTextureCreate(EngineTexture* texture);

/**
 * @brief destroy the given subTexture from the memory
 * @param texture the texture to destroy
 */
void EngineSubTextureDestroy(EngineSubTexture* texture);

/**
 * @brief set the begining of the sub texture, same as EngineSubTextureSetUV1
 * @param texture the subtexture to change
 * @param x the x axis to set
 * @param y the y axis to set
 * TODO #18
 */
void EngineSubTextureSetBegin(EngineSubTexture* texture, uint32_t x, uint32_t y);


/**
 * @brief set the begining of the sub texture, same as EngineSubTextureSetUV1
 * @param texture the subtexture to change
 * @param x the x axis to set
 * @param y the y axis to set
 * TODO #19
 */
void EngineSubTextureSetSize(EngineSubTexture* texture, uint32_t x, uint32_t y);

/**
 * @brief move the area that is selected by the sub texture
 * 
 * @param texture the sub texture to change
 * @param x the new begin x
 * @param y the new begin y
 * TODO #21
 */
void EngineSubTextureMove(EngineSubTexture* texture, uint32_t x, uint32_t y);

/**
 * @brief set the size of the area that is selected by the sub texture
 * 
 * @param texture the sub texture to change
 * @param width the new width
 * @param height the new height
 */
void EngineSubTextureResized(EngineSubTexture* texture, uint32_t width, uint32_t height);
