#include "ShaderProgram.h"
#include "Logger.h"
#include <fstream>
#include <vector>


ShaderProgram::ShaderProgram() : _programID(0), _vertexShaderID(0), _fragmentShaderID(0), _numAttributes(0)
{
}


ShaderProgram::~ShaderProgram()
{
}

void ShaderProgram::compileShaders(const std::string& vertexShaderPath, const std::string& fragmentShaderPath) {
	_programID = glCreateProgram();

	_vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	if (_vertexShaderID == 0) {
		logError("Couldnt create vertexshader");
	}
	_fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
	if (_fragmentShaderID == 0) {
		logError("couldn't create Fragmentshader ");
	}

	compileShader(vertexShaderPath, _vertexShaderID);
	compileShader(fragmentShaderPath, _fragmentShaderID);
}

void ShaderProgram::compileShader(const std::string& path, GLuint id) {

	std::ifstream file(path);
	if (file.fail()) {
		logError("Couldn't open vertexFile");
	}

	std::string fileContents = "";
	std::string line;

	while (std::getline(file, line)) {
		fileContents += line + "\n";
	}

	file.close();
	const char* pntr = fileContents.c_str();
	glShaderSource(id, 1, &pntr, nullptr);

	glCompileShader(id);

	GLint success = 0;
	glGetShaderiv(id, GL_COMPILE_STATUS, &success);
	if (success == GL_FALSE) {
		GLint maxLength = 0;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &maxLength);

		std::vector<char> errorLog(maxLength);
		glGetShaderInfoLog(id, maxLength, &maxLength, &errorLog[0]);

		glDeleteShader(id);

		logError(&(errorLog[0]));
	}
}

void ShaderProgram::addAttribute(const std::string& attributeName) {
	glBindAttribLocation(_programID, _numAttributes++, attributeName.c_str());
}

void ShaderProgram::linkShaders() {
	glAttachShader(_programID, _vertexShaderID);
	glAttachShader(_programID, _fragmentShaderID);

	glLinkProgram(_programID);

	GLint isLinked = 0;
	glGetProgramiv(_programID, GL_LINK_STATUS, (int *)&isLinked);
	if (isLinked == GL_FALSE) {

		GLint maxLength = 0;
		glGetProgramiv(_programID, GL_INFO_LOG_LENGTH, &maxLength);

		std::vector<char> infoLog(maxLength);
		glGetProgramInfoLog(_programID, maxLength, &maxLength, &infoLog[0]);

		glDeleteProgram(_programID);
		glDeleteShader(_vertexShaderID);
		glDeleteShader(_fragmentShaderID);

		logError((&infoLog[0]));
	}

	glDetachShader(_programID, _vertexShaderID);
	glDetachShader(_programID, _fragmentShaderID);
	glDeleteShader(_vertexShaderID);
	glDeleteShader(_fragmentShaderID);
}

void ShaderProgram::use() {
	glUseProgram(_programID);
	for (int i = 0; i < _numAttributes; i++)
	{
		glEnableVertexAttribArray(i);
	}
}

void ShaderProgram::disable() {
	glUseProgram(0);
	for (int i = 0; i < _numAttributes; i++)
	{
		glDisableVertexAttribArray(i);
	}
}