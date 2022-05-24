#pragma once

#include "../core.h"

typedef enum{
	ENGINE_RENDER_COMMAND_DRAW_POINTS,
	ENGINE_RENDER_COMMAND_DRAW_LINES,
	ENGINE_RENDER_COMMAND_DRAW_RECTS,
	ENGINE_RENDER_COMMAND_CLEAR,
	ENGINE_RENDER_COMMAND_SET_CLEAR_COLOR,
} EngineRenderCommandType;

typedef struct{
	void *data;
	uint16_t dataSize;
	EngineRenderCommandType type;
} EngineRenderCommand;

typedef struct{
	float x, y;
} PointData;

typedef struct{
	float x1, y1;
	float x2, y2;
} LineData;

typedef struct{
	float x1, y1;
	float x2, y2;
} RectData;

typedef struct{
	float x, y; // coords of the center of the texture
	float w, h;
	float UVx1, UVy1;
	float UVx2, UVy2;
	uint32_t textureID;
} TextureData;