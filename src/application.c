#include "engine/application.h"

// std
#include <assert.h>
#include <pthread.h>

void EngineApplicationCreateWindow(EngineApplication* app){
	assert(app != NULL && "cannot create a window from a NULL application");
	EngineWindowDef* def = EngineWindowCreateDef();
	app->window = EngineWindowCreate(def);
}

void EngineApplicationCreateRenderer(EngineApplication* app){
	assert(app != NULL && "cannot create a renderer from a NULL application");
	app->renderer = EngineRendererCreate(app->window, 400);
}

EngineApplication* EngineApplicationCreate(void){
	EngineApplication* app = malloc(sizeof(EngineApplication));
	MALLOC_CHECK(app);

	EngineApplicationCreateWindow(app);
	EngineApplicationCreateRenderer(app);

	app->gameThreadFinished = false;
	app->renderThreadFinished = false;
	app->gameThreadLock = PTHREAD_MUTEX_INITIALIZER;
	app->renderThreadLock = PTHREAD_MUTEX_INITIALIZER;
	app->gameThreadCond = PTHREAD_COND_INITIALIZER;
	app->renderThreadCond = PTHREAD_COND_INITIALIZER;

	return app;
}

void EngineApplicationDestroy(EngineApplication* app){
	assert(app != NULL && "cannot destroy a NULL application");

	EngineRendererDestroy(app->renderer);
	EngineWindowDestroy(app->window);
	free(app);
}

void EngineAppWaitForRenderer(EngineApplication* app){
	assert(app != NULL && "cannot wait for a NULL application");
	pthread_mutex_lock(&app->renderThreadLock);
	while (app->renderThreadFinished == false){
		pthread_cond_wait(&app->renderThreadCond, &app->renderThreadLock);
	}
	pthread_mutex_unlock(&app->renderThreadLock);
}

void EngineAppWaitForGame(EngineApplication* app){
	assert(app != NULL && "cannot wait for a NULL application");
	pthread_mutex_lock(&app->gameThreadLock);
	while (app->gameThreadFinished == false){
		pthread_cond_wait(&app->gameThreadCond, &app->gameThreadLock);
	}
	pthread_mutex_unlock(&app->gameThreadLock);
}

void EngineAppGameThreadFinished(EngineApplication* app){
	assert(app != NULL && "cannot finish a NULL application");
	pthread_mutex_lock(&app->gameThreadLock);
	app->gameThreadFinished = true;
	pthread_cond_signal(&app->gameThreadCond);
	pthread_mutex_unlock(&app->gameThreadLock);
}

void EngineAppRenderThreadFinished(EngineApplication* app){
	assert(app != NULL && "cannot finish a NULL application");
	pthread_mutex_lock(&app->renderThreadLock);
	app->renderThreadFinished = true;
	pthread_cond_signal(&app->renderThreadCond);
	pthread_mutex_unlock(&app->renderThreadLock);
}

void EngineAppGameThreadBegin(EngineApplication* app){
	assert(app != NULL && "cannot begin a NULL application");
	pthread_mutex_lock(&app->gameThreadLock);
	app->gameThreadFinished = false;
	pthread_cond_signal(&app->gameThreadCond);
	pthread_mutex_unlock(&app->gameThreadLock);
}

void EngineAppRenderThreadBegin(EngineApplication* app){
	assert(app != NULL && "cannot begin a NULL application");
	pthread_mutex_lock(&app->renderThreadLock);
	app->renderThreadFinished = false;
	pthread_cond_signal(&app->renderThreadCond);
	pthread_mutex_unlock(&app->renderThreadLock);
}

void EngineApplicationGameThread(void* appPtr){
	EngineApplication* app = appPtr;
	assert(app != NULL && "cannot run a NULL application");

	while (app->running){
		EngineAppRenderThreadBegin(app);
		// update

		EngineRendererSetDrawColor(app->renderer, 255, 0, 0, 255);
		EngineRendererDrawLine(app->renderer, 10, 40, 90, 240);

		EngineAppGameThreadFinished(app);
		EngineAppWaitForRenderer(app);
	}
}

void EngineApplicationRun(EngineApplication* app){
	assert(app != NULL && "cannot run a NULL application");
	pthread_create(&app->gameThread, NULL, (void*)&EngineApplicationGameThread, app);

	while (app->running){
		EngineAppGameThreadBegin(app);
		
		
		EngineRendererDraw(app->renderer);
		EngineAppWaitForGame(app);
		
		EngineRendererSwap(app->renderer);
		EngineWindowUpdate(app->window);
		
		EngineRendererSetDrawColor(app->renderer, 0, 0, 0, 255);
		EngineRendererClear(app->renderer);

		EngineSleep(16);
		EngineAppRenderThreadFinished(app);
	}

	pthread_join(app->gameThread, NULL);
}
