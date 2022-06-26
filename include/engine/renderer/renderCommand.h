#pragma once

#include "../core.h"

typedef enum{
	ENGINE_RENDER_COMMAND_NONE,
	ENGINE_RENDER_COMMAND_DRAW_POINTS,
	ENGINE_RENDER_COMMAND_DRAW_LINES_STRIP,
	ENGINE_RENDER_COMMAND_DRAW_LINES,
	ENGINE_RENDER_COMMAND_DRAW_RECTS,
	ENGINE_RENDER_COMMAND_DRAW_FILLED_RECTS,
	ENGINE_RENDER_COMMAND_CLEAR,
	ENGINE_RENDER_COMMAND_SET_DRAW_COLOR,
	ENGINE_RENDER_COMMAND_DRAW_TEXTURE,
	ENGINE_RENDER_COMMAND_DRAW_SUBTEXTURE,
	ENGINE_RENDER_COMMAND_DRAW_ROTATED_TEXTURE,
	ENGINE_RENDER_COMMAND_DRAW_ROTATED_SUBTEXTURE,
} EngineRenderCommandType;

typedef struct{
	void *data;
	EngineRenderCommandType type;
	uint16_t count;
} EngineRenderCommand;