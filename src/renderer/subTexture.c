#include <assert.h>
#include "engine/core.h"
#include "engine/renderer/subTexture.h"

EngineSubTexture* EngineSubTextureCreate(EngineTexture* texture){
	EngineSubTexture* subTexture = malloc(sizeof(EngineSubTexture));
	MALLOC_CHECK(subTexture);
	subTexture->texture = texture;
	subTexture->x = 0;
	subTexture->y = 0;
	subTexture->w = 0; // texture->width
	subTexture->h = 0; // texture->height
	return subTexture;
}

void EngineSubTextureSetBegin(EngineSubTexture* texture, uint32_t x, uint32_t y){
	EngineSubTextureMove(texture, x, y);
}


void EngineSubTextureMove(EngineSubTexture* texture, uint32_t x, uint32_t y){
	assert(texture && "cannot set the UV of a NULL sub texture");
	texture->x = x;
	texture->y = y;
}

void EngineSubTextureResized(EngineSubTexture* texture, uint32_t width, uint32_t height){
	assert(texture && "cannot set the UV of a NULL sub texture");
	texture->w = width;
	texture->h = height;
}