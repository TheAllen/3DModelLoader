#include "mesh.h"
#include <iostream>
#include <sstream>
#include <fstream>

Mesh::Mesh()
	: mLoaded(false)
{

}

Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &mVAO);
	glDeleteBuffers(1, &mVBO);
}

void Mesh::draw()
{
	//If not loaded, exit
	if (!mLoaded) return;

	glBindVertexArray(mVAO);
	glDrawArrays(GL_TRIANGLES, 0, mVertices.size());
	glBindVertexArray(0);
}

void Mesh::initBuffers()
{
	/*VAO*/
	glGenVertexArrays(1, &mVAO);
	glBindVertexArray(mVAO);

	/*VBO*/
	glGenBuffers(1, &mVBO);
	glBindBuffer(GL_ARRAY_BUFFER, mVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * mVertices.size(), &mVertices[0], GL_STATIC_DRAW);

	/*Attrib Pointer*/
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)0);
	glEnableVertexAttribArray(0);

	//Tex coord
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

bool Mesh::loadOBJ(const std::string& filename)
{
	std::vector<unsigned int> vertexIndices, uvIndices;
	std::vector<glm::vec3> tempVertices;
	//std::vector<glm::vec3> tempNormals;
	std::vector<glm::vec2> tempUVs;

	if (filename.find(".obj") != std::string::npos)
	{
		std::ifstream fin(filename, std::ios::in);
		if (!fin)
		{
			std::cerr << "Cannot open" << std::endl;
			return false;
		}

		std::cout << "Loading OBJ file " << filename << "..." << std::endl;

		std::string lineBuffer;
		while (std::getline(fin, lineBuffer))
		{
			if (lineBuffer.substr(0, 2) == "v ")
			{
				std::istringstream v(lineBuffer.substr(2));
				glm::vec3 vertex;
				v >> vertex.x; v >> vertex.y; v >> vertex.z;
				tempVertices.push_back(vertex);
			}

			// Normal data
			/*else if (lineBuffer.substr(0, 3) == "vn ")
			{
				std::istringstream s(lineBuffer.substr(2));
				glm::vec3 normal;
				s >> normal.x;
				s >> normal.y;
				s >> normal.z;
				tempNormals.push_back(normal);
			}*/

			else if (lineBuffer.substr(0, 3) == "vt ")
			{
				std::istringstream vt(lineBuffer.substr(3));
				glm::vec2 uv;
				vt >> uv.s; vt >> uv.t;
				tempUVs.push_back(uv);
			}
			else if (lineBuffer.substr(0, 2) == "f ")
			{
				int p1, p2, p3; //To store mesh index;
				int t1, t2, t3;
				int n1, n2, n3;
				const char* face = lineBuffer.c_str();
				int match = sscanf_s(face, "f %d/%d/%d %d/%d/%d %d/%d/%d",
					&p1, &t1, &n1,
					&p2, &t2, &n2,
					&p3, &t3, &n3);
				if (match != 9)
				{
					std::cout << "Failed to parse OBJ file using our very simple OBJ loader" << std::endl;
				}

			
				vertexIndices.push_back(p1);
				vertexIndices.push_back(p2);
				vertexIndices.push_back(p3);

				/*normalIndices.push_back(n1);
				normalIndices.push_back(n2);
				normalIndices.push_back(n3);*/


				uvIndices.push_back(t1);
				uvIndices.push_back(t2);
				uvIndices.push_back(t3);
			}
		}

		fin.close();

		//For each vertex of each triangle
		for (unsigned int i = 0; i < vertexIndices.size(); i++) 
		{
			// Get the attributes using the indices
			glm::vec3 vertex = tempVertices[vertexIndices[i] - 1];
			//glm::vec3 normals = tempNormals[normalIndices[i] - 1];
			glm::vec2 uv = tempUVs[uvIndices[i] - 1];

			Vertex meshVertex;
			meshVertex.position = vertex;
			meshVertex.texCoord = uv;
			//meshVertex.normals = normals;

			mVertices.push_back(meshVertex);
		}

		initBuffers();

		return (mLoaded = true);
	}

	return false;
}

void Mesh::loadOBJ1(const char* path, std::vector<glm::vec3>& positions, std::vector<glm::vec3>& normals, std::vector<glm::vec2>& uvCoords)
{
	std::ifstream in(path, std::ios::in);
	in.exceptions(std::ifstream::badbit);

	/*Error Handler*/
	if (!in)
	{
		std::stringstream errorMessage;
		errorMessage << "Unable to open .OBJ file " << path << "." << std::endl;
		return;
	}

	std::string currentline;
	/*Positon*/
	int positionIndexA;
	int positionIndexB;
	int positionIndexC;
	/*Normals*/
	int normalIndexA;
	int normalIndexB;
	int normalIndexC;
	/*UVs*/
	int uvCoordIndexA;
	int uvCoordIndexB;
	int uvCoordIndexC;
	std::vector<glm::vec3> temp_positions;
	std::vector<glm::vec3> temp_normals;
	std::vector<glm::vec2> temp_uvCoords;

	while (!in.eof())
	{
		try {
			std::getline(in, currentline);
		}
		catch (const std::ifstream::failure &e)
		{
			in.close();
			std::stringstream errorMessage;
			errorMessage << "Error calling reading line " << e.what() << std::endl;
			return;
		}

		//Vertex data 
		if (currentline.substr(0, 2) == "v ")
		{
			//Get entire line excluding the first two chars
			std::istringstream s(currentline.substr(2));
			glm::vec3 vertex;
			s >> vertex.x;
			s >> vertex.y;
			s >> vertex.z;
			temp_positions.push_back(vertex);
		}

		// Normal data
		else if (currentline.substr(0, 3) == "vn ")
		{
			std::istringstream s(currentline.substr(2));
			glm::vec3 normal;
			s >> normal.x;
			s >> normal.y;
			s >> normal.z;
			temp_normals.push_back(normal);
		}

		//Texture coordinates
		else if (currentline.substr(0, 3) == "vt ")
		{
			std::istringstream s(currentline.substr(2));
			glm::vec2 textureCoords;
			s >> textureCoords.x;
			s >> textureCoords.y;
			temp_uvCoords.push_back(textureCoords);
		}

		else if (currentline.substr(0, 2) == "f ")
		{
			int index;

			int numberOfIndexMatches = sscanf_s(currentline.c_str(), "f %d/%d/%d", &index, &index, &index);
			if (numberOfIndexMatches == 3)
			{
				sscanf_s(currentline.c_str(), "f %d/%d/%d %d/%d/%d %d/%d/%d",
					&positionIndexA, &uvCoordIndexA, &normalIndexA,
					&positionIndexB, &uvCoordIndexB, &normalIndexB,
					&positionIndexC, &uvCoordIndexC, &normalIndexC);

				//Starting at 0
				uvCoordIndexA--;
				uvCoordIndexB--;
				uvCoordIndexC--;

				uvCoords.push_back(temp_uvCoords[uvCoordIndexA]);
				uvCoords.push_back(temp_uvCoords[uvCoordIndexB]);
				uvCoords.push_back(temp_uvCoords[uvCoordIndexC]);
			}
			else
			{
				sscanf_s(currentline.c_str(), "f %d//%d %d//%d %d//%d", &positionIndexA, &normalIndexA,
					&positionIndexB, &normalIndexB,
					&positionIndexC, &normalIndexC);
			}

			positionIndexA--;
			positionIndexB--;
			positionIndexC--;
			normalIndexA--;
			normalIndexB--;
			normalIndexC--;

			positions.push_back(temp_positions[positionIndexA]);
			positions.push_back(temp_positions[positionIndexB]);
			positions.push_back(temp_positions[positionIndexC]);

			normals.push_back(temp_normals[normalIndexA]);
			normals.push_back(temp_normals[normalIndexB]);
			normals.push_back(temp_normals[normalIndexC]);

		}
	}

	in.close();

}

void Mesh::loadOBJ2(const char* path, std::vector<glm::vec3>& position, std::vector<glm::vec3>& normals)
{

}