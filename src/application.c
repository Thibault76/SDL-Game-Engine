#include "engine/application.h"

// std
#include <assert.h>
#include <pthread.h>

void EngineAppOnEvent(EngineEvent* event){
	EngineApplication* app = event->userData;
	
	switch (event->type){
		case ENGINE_EVENT_TYPE_WINDOW_CLOSED: app->running = false;
	}
}

void EngineApplicationCreateWindow(EngineApplication* app){
	assert(app != NULL && "cannot create a window from a NULL application");
	EngineWindowDef* def = EngineWindowCreateDef();
	app->window = EngineWindowCreate(def);
}

void EngineApplicationCreateRenderer(EngineApplication* app){
	assert(app != NULL && "cannot create a renderer from a NULL application");
	app->renderer = EngineRendererCreate(app->window, 500);
}

EngineApplication* EngineApplicationCreate(void){
	EngineApplication* app = malloc(sizeof(EngineApplication));
	MALLOC_CHECK(app);

	EngineApplicationCreateWindow(app);
	EngineApplicationCreateRenderer(app);

	EngineWindowSetEventCallback(app->window, &EngineAppOnEvent);
	app->window->userData = app;

	pthread_barrier_init(&app->gameThreadFinished, NULL, 2);

	// ! ----------------------------------------------
	pthread_barrier_init(&app->renderThreadFinished, NULL, 2);
	// ! ----------------------------------------------

	return app;
}

void EngineApplicationDestroy(EngineApplication* app){
	assert(app != NULL && "cannot destroy a NULL application");

	EngineRendererDestroy(app->renderer);
	EngineWindowDestroy(app->window);

	pthread_barrier_destroy(&app->gameThreadFinished);
	pthread_barrier_destroy(&app->renderThreadFinished);

	free(app);
}

void* EngineApplicationGameThread(void* appPtr){
	EngineApplication* app = appPtr;
	assert(app != NULL && "cannot run a NULL application");

	EngineTexture* texture = EngineTextureCreateFromPath(app->renderer, "gradient.bmp");

	int j=500;
	while (app->running){
		uint64_t start = EngineGetTicks();

		EngineRendererSetDrawColor(app->renderer, 255, 255, 255, 255);
		for (int i=0; i<j; i++){
			EngineRendererDrawPoint(app->renderer, rand() % 1080, rand() % 720);
		}

		pthread_barrier_wait(&app->gameThreadFinished);
		pthread_barrier_wait(&app->renderThreadFinished);
		
		uint64_t end = EngineGetTicks();
		printf("delta : %llfs || j : %d\n", ((float)end / 1000.f) - ((float)start / 1000.f), j);
	}

	EngineTextureDestroy(texture);
	pthread_exit(NULL);
}

void EngineApplicationRun(EngineApplication* app){
	assert(app != NULL && "cannot run a NULL application");
	if (pthread_create(&app->gameThread, NULL, (void*)&EngineApplicationGameThread, app) != 0){
		perror("Failed to create agame thread");
	}

	while (app->running){
		EngineRendererDraw(app->renderer);
		pthread_barrier_wait(&app->gameThreadFinished);
		
		EngineRendererSwap(app->renderer);
		EngineWindowUpdate(app->window);
		
		EngineRendererSetDrawColor(app->renderer, 0, 0, 0, 255);
		EngineRendererClear(app->renderer);

		EngineSleep(16);
		pthread_barrier_wait(&app->renderThreadFinished);
	}

	pthread_join(app->gameThread, NULL);
}
