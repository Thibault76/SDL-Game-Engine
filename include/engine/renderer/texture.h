#pragma once

typedef struct{
	void* texture;
} EngineTexture;

/**
 * @brief create an emtpy texture
 * @return EngineTexture* 
 */
EngineTexture* EngineTextureCreate();

/**
 * @brief destroy a texture
 * @warning the texture pointer is not destroyed during this prosses
 * 
 * @param texture the texture to destroy
 * @return void* 
 */
void EngineTextureDestroy(EngineTexture* texture);

// test
EngineTexture* EngineTextureCreateFromPath(void *rendererPtr, const char* path);