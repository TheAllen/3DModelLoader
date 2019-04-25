#pragma once
#ifndef MESH_H
#define MESH_H

#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <GL/glew.h>
#include <glm/glm.hpp>


struct Vertex
{
	glm::vec3 position;
	glm::vec2 texCoord;
};

class Mesh
{
public:
	Mesh();
	~Mesh();

	bool loadOBJ(const std::string& filename);
	/*With UV coordinates*/
	void loadOBJ1(const char* path, std::vector<glm::vec3>&, std::vector<glm::vec3>&, std::vector<glm::vec2>&);
	/*Without UV coordinates*/
	void loadOBJ2(const char* path, std::vector<glm::vec3>&, std::vector<glm::vec3>&);
	
	void draw();

private:

	void initBuffers();

	bool mLoaded;
	std::vector<Vertex> mVertices;
	GLuint mVBO, mVAO;
};

#endif