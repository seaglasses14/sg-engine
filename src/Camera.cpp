#include "Camera.h"
#include "Core/Log.h"
#include <iostream>

Camera::Camera(glm::vec3 position, glm::vec3 worldUp, float yaw, float pitch)
	: Speed(SPEED),
	  Sensitivity(SENSITIVITY),
	  Fov(FOV)
{
	Position = position;
	WorldUp = worldUp;
	Yaw = yaw;
	Pitch = pitch;
	updateCameraVectors();
}

Camera::Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch)
	: Speed(SPEED),
	  Sensitivity(SENSITIVITY),
	  Fov(FOV)
{
	Position = glm::vec3(posX, posY, posZ);
	WorldUp = glm::vec3(upX, upY, upZ);
	Yaw = yaw;
	Pitch = pitch;
	updateCameraVectors();
}

glm::mat4 Camera::GetViewMatrix()
{
	//return glm::lookAt(Position, Position + Front, Up);
	return LookAt(Position, Position + Front, Up);
}

void Camera::ProcessDirectionInput(Camera_Movement direction, float deltaTime)
{
	glm::vec3 movementFront = Front;
	if (FPS_MODE)
		movementFront.y = 0.0f;
	float velocity = Speed * deltaTime;
	if (direction == FORWARD)
		Position += movementFront * velocity;
	if (direction == BACKWARD)
		Position -= movementFront * velocity;
	if (direction == RIGHT)
		Position += Right * velocity;
	if (direction == LEFT)
		Position -= Right * velocity;
	if (!FPS_MODE)
	{
		if (direction == UPWARD)
			Position += WorldUp * velocity;
		if (direction == DOWNWARD)
			Position -= WorldUp * velocity;
	}
	if (direction == FORWARD)
		LOG_INFO("Forward");
	if (direction == BACKWARD)
		LOG_INFO("Backward");
	if (direction == RIGHT)
		LOG_INFO("Right");
	if (direction == LEFT)
		LOG_INFO("Left");
	if (!FPS_MODE)
	{
		if (direction == UPWARD)
			LOG_INFO("Upward");
		if (direction == DOWNWARD)
			LOG_INFO("Downward");
	}
}

void Camera::ProcessRotationInput(float xoffset, float yoffset, bool constrainPitch)
{
	xoffset *= Sensitivity;
	yoffset *= Sensitivity;

	Yaw = glm::mod(Yaw + xoffset, 360.0f);
	Pitch += yoffset;

	if (constrainPitch)
	{
		if (Pitch > 89.0f)
			Pitch = 89.0f;
		if (Pitch < -89.0f)
			Pitch = -89.0f;
	}

	updateCameraVectors();
}

void Camera::ProcessScrollInput(float yoffset)
{
	Fov -= yoffset;
	if (Fov < FOV_MIN)
		Fov = FOV_MIN;
	if (Fov > FOV_MAX)
		Fov = FOV_MAX;
}

void Camera::updateCameraVectors()
{
	if (!FPS_MODE)
	{
		glm::vec3 direction;
		direction.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
		direction.y = sin(glm::radians(Pitch));
		direction.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
		Front = glm::normalize(direction);
		Right = glm::normalize(glm::cross(Front, WorldUp));
		Up = glm::normalize(glm::cross(Right, Front));
	}
	else
	{
		glm::vec3 direction;
		direction.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
		direction.y = sin(glm::radians(Pitch));
		direction.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
		Front = glm::normalize(direction);
		Right = glm::normalize(glm::cross(Front, WorldUp));
		Up = glm::normalize(glm::cross(Right, Front));
	}
}

glm::mat4 Camera::LookAt(glm::vec3 eye, glm::vec3 target, glm::vec3 up)
{
	glm::mat4 translationMatrix(1.0f);
	translationMatrix = glm::translate(translationMatrix, -eye);

	glm::vec3 d = glm::normalize(eye - target);
	//d = camera direction (z axis)
	glm::vec3 r = glm::normalize(glm::cross(up, d));
	//r = positive right axis vector (x axis)
	glm::vec3 u = glm::normalize(glm::cross(d, r));
	//u = camera up vector (y axis)

	glm::mat4 basisMatrix(
		r.x, u.x, d.x, 0,
		r.y, u.y, d.y, 0,
		r.z, u.z, d.z, 0,
		0, 0, 0, 1
	);

	return basisMatrix * translationMatrix;
}