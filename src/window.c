// std
#include <stdio.h>
#include <assert.h>

// engine
#include "engine/window.h"

// libs
#include <libs/SDL2/SDL.h>

EngineWindowDef* EngineCreateWindowDef(){
	EngineWindowDef *def = malloc(sizeof(EngineWindowDef*));
	def->width = 1080;
	def->height = 720;

	strcpy(def->title, "SDL Game Engine");

	def->icon = NULL;
	return def;
}

EngineWindow* EngineCreateWindow(EngineWindowDef* def){
	assert(def != NULL && "cannot create a window from a NULL definition");
	EngineWindow* window = malloc(sizeof(EngineWindow*));


	return window;
}

EngineWindow* EngineDestroyWindow(EngineWindow* window){

}
