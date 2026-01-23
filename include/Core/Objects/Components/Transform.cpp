#include "Transform.h"

#include <glm/gtc/matrix_transform.hpp>

Transform::Transform()
{
	location = glm::vec3(0, 0, 0);
	rotation = glm::vec3(0, 0, 0);
	scale = glm::vec3(1, 1, 1);
	
	UpdateModel();
}

void Transform::SetLocation(glm::vec3& pLocation)
{
	location = pLocation;
	UpdateModel();
}

void Transform::SetRotation(glm::vec3& pRotation)
{
	rotation = pRotation;
	UpdateModel();
}

void Transform::SetScale(glm::vec3& pScale)
{
	scale = pScale;
	UpdateModel();
}

void Transform::UpdateModel()
{
	glm::mat4 newModel = glm::mat4(1.f);
	newModel = glm::rotate
}
