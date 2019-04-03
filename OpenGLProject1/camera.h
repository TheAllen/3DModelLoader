#pragma once

#include <iostream>
#include <stdio.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Camera
{
	class Camera
	{
	public:
		Camera();
		~Camera();

		bool firstMove;

		glm::vec3 getCameraPos(const glm::vec3&) const;
		glm::vec3 getCameraFront(const glm::vec3&) const;
		glm::vec3 getCameraUp(const glm::vec3&) const;

	private:
		glm::vec3 cameraPos;
		glm::vec3 cameraFront;
		glm::vec3 cameraUp;
	};
}