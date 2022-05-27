#include <engine/engine.h>
#include <stdio.h>
#include <stdlib.h>
#include "engine/maths.h"

int main(int argv, char **args){
	/*
	EngineApplication *app = EngineApplicationCreate();
	EngineApplicationRun(app);
	EngineApplicationDestroy(app); */

	Vector *v = EngineMathsNewVector(4, 1, 3.0, 6.8, 99);
	printVector(v);
	v = EngineMathsFreeVector(v);

	return EXIT_SUCCESS;
}