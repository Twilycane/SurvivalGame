#include "Engine.h"

int main(int argc, char* args[]) {
	Engine engine;
	engine.init();
	engine.gameLoop();
	engine.exit();
	return 0;
}