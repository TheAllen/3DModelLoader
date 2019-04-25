#pragma once

#include <GL/glew.h>
#include "stb_image.h"

class Texture
{
public:
	Texture();
	Texture(const char* fileLocation);
	~Texture();

	bool loadTexture();
	bool loadTextureA();
	void useTexture();
	void clearTexture();

private:
	GLuint textureID;

	int width;
	int height;
	int bitDepth;

	const char* fileLocation;
};