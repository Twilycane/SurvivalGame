#pragma once
#include <string>
#include <GL/glew.h>

class ShaderProgram
{
public:
	ShaderProgram();
	~ShaderProgram();

	void compileShaders(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
	void addAttribute(const std::string& attributeName);
	void linkShaders();

	void use();
	void disable();
private:
	void compileShader(const std::string& filePath, GLuint id);
	int _numAttributes;
	GLuint _programID;
	GLuint _vertexShaderID;
	GLuint _fragmentShaderID;
};

