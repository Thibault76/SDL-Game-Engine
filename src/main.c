#include <engine/engine.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct{
	EngineWindow* window;
	Bool running;
} Application;

int main(int argv, char **args){
	/*
	Application* app = malloc(sizeof(Application));
	MALLOC_CHECK(app);

	EngineWindowDef* windowDef = EngineWindowCreateDef();
	app->window = EngineWindowCreate(windowDef);

	app->running = true;
	while (app->running){
		EngineWindowUpdate(app->window);
	}

	free(app);
	*/

	QueuePreproStruct *q = EngineQueuePreproNew(3, 5);
	EngineQueuePreproPrintAllElementsInt(q);
	EngineQueuePreproPushElement(q, (void*)3);
	EngineQueuePreproPushElement(q, (void*)5);
	EngineQueuePreproPrintAllElementsInt(q);
	EngineQueuePreproPrintUsedElementsInt(q);
	EngineQueuePreproPushElement(q, (void*)7);
	EngineQueuePreproPrintAllElementsInt(q);
	EngineQueuePreproPrintUsedElementsInt(q);
	EngineQueuePreproPushElement(q, (void*)10);
	EngineQueuePreproPrintAllElementsInt(q);
	EngineQueuePreproPrintUsedElementsInt(q);
	EngineQueuePreproPopElement(q);
	EngineQueuePreproPrintAllElementsInt(q);
	EngineQueuePreproPrintUsedElementsInt(q);
	EngineQueuePreproPopElement(q);
	EngineQueuePreproPrintAllElementsInt(q);
	EngineQueuePreproPrintUsedElementsInt(q);
	EngineQueuePreproClearAll(q);

	return EXIT_SUCCESS;
}