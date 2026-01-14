#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

enum Camera_Movement
{
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT,
	UPWARD,
	DOWNWARD
};

//default values
const float YAW			= -90.0f;
const float PITCH		=   0.0f;
const float SPEED		=   2.5f;
const float SENSITIVITY =   0.1f;
const float FOV			=  45.0f;
const float FOV_MIN		=   1.0f;
const float FOV_MAX		=  45.0f;
const bool FPS_MODE		=   false;

class Camera
{
public:
	glm::vec3 Position;
	glm::vec3 Front;
	glm::vec3 Up;
	glm::vec3 Right;
	glm::vec3 WorldUp;

	float Yaw;
	float Pitch;
	float Speed;
	float Sensitivity;
	float Fov;

	Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 worldUp = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH);
	Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw = YAW, float pitch = PITCH);
	glm::mat4 GetViewMatrix();
	void ProcessDirectionInput(Camera_Movement direction, float deltaTime);
	void ProcessRotationInput(float xoffset, float yoffset, bool constrainPitch = true);
	void ProcessScrollInput(float yoffset);

private:
	void updateCameraVectors();
	glm::mat4 LookAt(glm::vec3 eye, glm::vec3 target, glm::vec3 up);
};