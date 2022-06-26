#include "engine/core.h"
#include "engine/renderer/texture.h"
#include "engine/renderer/renderer.h"

#include <assert.h>
#include <libs/SDL2/SDL.h>

EngineTexture* EngineTextureCreate(){
	EngineTexture* texture = malloc(sizeof(EngineTexture));
	MALLOC_CHECK(texture);
	texture->texture = NULL;
	return texture;
}

void EngineTextureDestroy(EngineTexture* texture){
	if (texture) free(texture);
}

EngineTexture* EngineTextureCreateFromPath(void* rendererPtr, const char* path){
	EngineRenderer* renderer = (EngineRenderer*)rendererPtr;
	assert(renderer && "cannot load a texture with a NULL renderer");
	EngineTexture* texture = EngineTextureCreate();

	SDL_Surface* surface = SDL_LoadBMP(path);
	if (!surface){
		fprintf(stderr, "SDL_LoadBMP Error : %s", SDL_GetError());
		assert(false && "SDL_LoadBMP Error");
	}

	texture->texture = SDL_CreateTextureFromSurface((SDL_Renderer*)renderer->nativeRunderer, surface);
	
	if (!texture->texture){
		fprintf(stderr, "SDL_CreateTextureFromSurface Error : %s", SDL_GetError());
		assert(false && "SDL_CreateTextureFromSurface Error");
	}

	SDL_FreeSurface(surface);
	return texture;
}