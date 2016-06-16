#include "Logger.h"
#include <SDL.h>

void logError(const char* error) {
	std::cout << error << std::endl;
	getchar();
	SDL_Quit();
	exit(69);
}