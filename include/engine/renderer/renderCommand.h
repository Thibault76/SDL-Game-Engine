#pragma once

#include "../core.h"

typedef enum{
	ENGINE_RENDER_TOPOLOGY_POINTS,
	ENGINE_RENDER_TOPOLOGY_LINES,
	ENGINE_RENDER_TOPOLOGY_RECTS,
} EngineRenderTopology;

typedef struct{
	// TODO : replace with an array of vec2
	void* data; // a pointer to the preallocated dynamic array or texture struct
	EngineRenderTopology topology;
} EngineRenderCommand;