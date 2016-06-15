#pragma once
#include <chrono>
#include <iostream>
#include <string>
#include <fstream>
#include <cstddef>
#include <Windows.h>
#include <GL\glew.h>
#include <SDL.h>
#include "Logger.h"
#include "Vertex.h"
#define GLEW_STATIC 


class Engine
{
public:
	void init();
	void exit();
	void compileShaders();
	void compileShader(std::string path, GLuint id);
	void linkShaders();
	void gameLoop();
	void CheckShader(GLuint id);
	GLint uniColor;

	Engine();
	~Engine();
protected:
	bool gameOver;
	SDL_Window* _window;
	SDL_GLContext _context;
	GLuint _programID;
	GLuint _vertexID;
	GLuint _fragmentID;
	GLuint _vao;
	GLuint _vbo;
};

