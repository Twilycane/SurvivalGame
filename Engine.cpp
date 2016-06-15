#include "Engine.h"

Engine::Engine() : _window(nullptr), _vertexID(0), _fragmentID(0), _programID(0), gameOver(false){

}

void Engine::CheckShader(GLuint id)
{
	GLint status;
	glGetShaderiv(id, GL_COMPILE_STATUS, &status);
	if (status == GL_FALSE)
	{
		printf("Error compiling!\n");
	}
}

void Engine::compileShader(std::string path, GLuint id) {
	std::string contents = "";
	std::string line;
	
	std::ifstream file(path);
	while (std::getline(file, line)) {
		contents += line + "\n";
	}
	file.close();

	const char* contentsPtr = contents.c_str();
	glShaderSource(id, 1, &contentsPtr, nullptr);
	glCompileShader(id);
	CheckShader(id);
}

void Engine::linkShaders() {
	glAttachShader(_programID, _vertexID);
	glAttachShader(_programID, _fragmentID);

	

	glLinkProgram(_programID);
	glUseProgram(_programID);
	std::cout << gluErrorString(glGetError());
	glBindFragDataLocation(_programID, 0, "color");
	glBindAttribLocation(_programID, 0, "pos");
	glBindAttribLocation(_programID, 1, "inColor");
}

void Engine::compileShaders() {
	_vertexID = glCreateShader(GL_VERTEX_SHADER);
	_fragmentID = glCreateShader(GL_FRAGMENT_SHADER);

	compileShader("Shaders/BaseVertexShader.txt", _vertexID);
	compileShader("Shaders/BaseFragmentShader.txt", _fragmentID);

	linkShaders();
}

void Engine::init() {
	SDL_Init(SDL_INIT_EVERYTHING);

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

	_window = SDL_CreateWindow("Survival", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_OPENGL);
	_context = SDL_GL_CreateContext(_window);

	glewExperimental = GL_TRUE;
	glewInit();
	glGetError();

	Vertex triangle[3];
	triangle[0].position.x = 0.0f;
	triangle[0].position.y = 0.5f;

	triangle[1].position.x = -0.5f;
	triangle[1].position.y = -0.5f;

	triangle[2].position.x = 0.5f;
	triangle[2].position.y = -0.5f;

	for (int i = 0; i < 3; i++)
	{
		triangle[i].color.r = 255;
		triangle[i].color.g = 255;
		triangle[i].color.b = 255;
		triangle[i].color.a = 255;
	}

	glGenVertexArrays(1, &_vao);
	glBindVertexArray(_vao);


	glGenBuffers(1, &_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(triangle), triangle, GL_STATIC_DRAW);

	_programID = glCreateProgram();

	compileShaders();

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
	glVertexAttribPointer(1, 4, GL_UNSIGNED_INT, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, color));
}

void Engine::gameLoop() {
	SDL_Event e;
	while (!gameOver)
	{
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		if (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT) {
				gameOver = true;
			}
		}
		glDrawArrays(GL_TRIANGLES, 0, 3);
		SDL_GL_SwapWindow(_window);
	}
}

void Engine::exit() {
	glDeleteProgram(_programID);
	SDL_GL_DeleteContext(_context);
	SDL_DestroyWindow(_window);
	SDL_Quit();
}

Engine::~Engine() {

}