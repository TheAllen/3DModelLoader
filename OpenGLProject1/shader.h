#pragma once

#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>

#include "GL/glew.h"

class Shader
{
public:
	Shader();
	~Shader();

	void createFromStrings(const char*, const char*);
	void createFromFile(const char*, const char*);
	std::string readFile(const char* fileLocation);

	GLuint getProjectionLocation() const;
	GLuint getModelLocation() const;
	GLuint getViewLocation() const;

	void useShader();
	void clearShader();

private:
	GLuint shaderID, uniformProjection, uniformModel, uniformView;

	void compileShader(const char*, const char*);
	void addShader(GLuint program, const char* shaderCode, GLenum shaderType);

};