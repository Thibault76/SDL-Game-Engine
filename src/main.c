#include <engine/engine.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argv, char **args){
	EngineApplication *app = EngineApplicationCreate();
	EngineApplicationRun(app);
	EngineApplicationDestroy(app);
	return EXIT_SUCCESS;
}