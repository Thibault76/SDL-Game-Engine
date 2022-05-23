#include <engine/engine.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct{
	EngineWindow* window;
	Bool running;
} Application;

int main(int argc, char **argv){
	Application* app = malloc(sizeof(Application*));

	{
		EngineWindowDef* windowDef = EngineWindowCreateDef();
		app->window = EngineWindowCreate(windowDef);
	}

	app->running = true;
	while (app->running){
		EngineWindowUpdate(app->window);
	}
	

	return EXIT_SUCCESS;
}