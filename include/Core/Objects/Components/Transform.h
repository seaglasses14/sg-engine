#pragma once

#include "glm/glm.hpp"

class Transform
{
public:
	glm::vec3 location;
	glm::vec3 rotation;
	glm::vec3 scale;

	Transform();

	void SetLocation(glm::vec3& pLocation);
	void SetRotation(glm::vec3& pRotation);
	void SetScale(glm::vec3& pScale);

private:
	glm::mat4 model;
	void UpdateModel();
};

