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
	pthread_barrier_t gameThreadFinished;
	pthread_barrier_t renderThreadFinished;

} EngineApplication;

/**
 * @brief allocate an application and initilize it
 * @return EngineApplication* 
 */
EngineApplication* EngineApplicationCreate(void);

/**
 * @brief clear and destroy the given application from memory
 * @param app the application to destroy
 */
void EngineApplicationDestroy(EngineApplication* app);

/**
 * @brief start the execution of the application
 * @param app the application to execute
 */
void EngineApplicationRun(EngineApplication* app);