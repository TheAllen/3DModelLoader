#include "shader.h"

Shader::Shader()
{

}

Shader::~Shader()
{

}

void Shader::createFromStrings(const char* vertString, const char* fragString)
{

}

void Shader::createFromFile(const char* vertFilePath, const char* fragFilePath)
{

}

std::string Shader::readFile(const char* fileLocation)
{
	return "";
}

GLuint Shader::getProjectionLocation() const
{
	return 0;
}

GLuint Shader::getModelLocation() const
{
	return 0;
}

GLuint Shader::getViewLocation() const
{
	return 0;
}

void Shader::useShader()
{

}

void Shader::clearShader()
{

}

void Shader::compileShader(const char* vertexShader, const char* fragmentShader)
{

}

void Shader::addShader(GLuint program, const char* shaderCode, GLenum shaderType)
{

}