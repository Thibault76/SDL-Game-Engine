#pragma once

#include "core.h"
#include "renderer/renderer.h"
#include "window.h"

// std
#include <pthread.h>

typedef struct{
	EngineWindow* window;
	EngineRenderer* renderer;
	Bool running;

	// multithreading
	pthread_t gameThread;
	volatile Bool gameThreadFinished;
	volatile Bool renderThreadFinished;
	pthread_mutex_t gameThreadLock;
	pthread_mutex_t renderThreadLock;
	pthread_cond_t gameThreadCond;
	pthread_cond_t renderThreadCond;

} EngineApplication;

/**
 * @brief allocate an application and initilize it
 * @return EngineApplication* 
 */
EngineApplication* EngineApplicationCreate(void);

void EngineApplicationDestroy(EngineApplication* app);

void EngineApplicationRun(EngineApplication* app);