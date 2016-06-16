#pragma once
#include <SDL.h>
#include <GL\glew.h>
#include "Sprite.h"
#include "ShaderProgram.h"

enum class GameState{PLAY, EXIT};

class Engine
{
public:

	void run();

	Engine();
	~Engine();
private:
	void initSystems();
	void processInput();
	void gameLoop();
	void drawGame();
	void initShaders();

	SDL_Window* _window;
	unsigned int _screenWidth, _screenHeight;
	GameState _gameState;

	Sprite _sprite;

	ShaderProgram _colorProgram;
};

