#include "Logger.h"

void Logger::logError(const char* error) {
	std::cout << error << std::endl;
	getchar();
	SDL_Quit();
	exit(69);
}