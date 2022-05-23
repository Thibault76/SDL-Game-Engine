#include <engine/engine.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct{
	EngineWindow* window;
	Bool running;
} Application;

int main(int argv, char **args){
	printf("aaa\n");
	Application* app = malloc(sizeof(Application));
	MALLOC_CHECK(app);
	printf("aaa\n");

	EngineWindowDef* windowDef = EngineWindowCreateDef();
	printf("aaa\n");
	app->window = EngineWindowCreate(windowDef);

	app->running = true;
	while (app->running){
		EngineWindowUpdate(app->window);
	}

	free(app);

	return EXIT_SUCCESS;
}