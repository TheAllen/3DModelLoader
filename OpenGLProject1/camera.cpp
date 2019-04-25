
#include "camera.h"

namespace Camera
{
	Camera::Camera()
	{
		cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
		cameraFront = glm::vec3(0.0, 0.0, -1.0f);
		cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

		firstMove = true;
	}

	Camera::~Camera()
	{

	}

	glm::vec3 Camera::getCameraPos(const glm::vec3&) const
	{
		return cameraPos;
	}

	glm::vec3 Camera::getCameraFront(const glm::vec3&) const
	{
		return cameraFront;
	}

	glm::vec3 Camera::getCameraUp(const glm::vec3&) const
	{
		return cameraUp;
	}

	void Camera::updateView()
	{

	}

	void Camera::mouseMove()
	{

	}
}