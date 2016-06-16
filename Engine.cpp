#include "Engine.h"
#include <iostream>
#include "Logger.h"


Engine::Engine() : _window(nullptr), _screenHeight(600), _screenWidth(800), _gameState(GameState::PLAY){

}

Engine::~Engine() {

}

void Engine::initSystems() {
	SDL_Init(SDL_INIT_EVERYTHING);

	_window = SDL_CreateWindow("Survival", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _screenWidth, _screenHeight, SDL_WINDOW_OPENGL);
	if (_window == nullptr) {
		logError("Window Could not be created!");
	}

	SDL_GLContext glcontext = SDL_GL_CreateContext(_window);
	if (glcontext == nullptr) {
		logError("Context Failed");
	}

	glewExperimental = true;
	GLenum error = glewInit();
	if (error != GLEW_OK) {
		logError("glew could not initialize");
	}

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	initShaders();
}

void Engine::initShaders() {
	_colorProgram.compileShaders("Shaders/colorShader.vert", "Shaders/colorShader.frag");
	_colorProgram.addAttribute("vertexPosition");
	_colorProgram.linkShaders();
}

void Engine::run(){
	initSystems();
	_sprite.init(-1.0f, -1.0f, 1.0f, 1.0f);
	gameLoop();
}

void Engine::processInput() {
	SDL_Event evnt;
	while (SDL_PollEvent(&evnt))
	{
		switch (evnt.type)
		{
		case SDL_QUIT:
			_gameState = GameState::EXIT;
			break;
		case SDL_MOUSEMOTION:
			std::cout << evnt.motion.x << " " << evnt.motion.y << std::endl;
			break;
		}
	}
	
}

void Engine::drawGame() {
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	_colorProgram.use();
	_sprite.draw();
	_colorProgram.disable();

	SDL_GL_SwapWindow(_window);
}

void Engine::gameLoop() {
	while (_gameState != GameState::EXIT)
	{
		processInput();
		drawGame();
	}
}