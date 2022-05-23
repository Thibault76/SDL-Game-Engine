#include <engine/engine.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct{
	EngineWindow* window;
	Bool running;
} Application;

int main(int argv, char **args){
	Application* app = malloc(sizeof(Application));
	MALLOC_CHECK(app);

	EngineWindowDef* windowDef = EngineWindowCreateDef();
	app->window = EngineWindowCreate(windowDef);

	app->running = true;
	while (app->running){
		EngineWindowUpdate(app->window);
	}

	free(app);

	return EXIT_SUCCESS;
}