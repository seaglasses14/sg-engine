#pragma once

#include "glm/glm.hpp"
#include "Core/Objects/Components/Component.h"

class Transform : public Component
{
public:
	glm::vec3 location;
	glm::vec3 rotation;
	glm::vec3 scale;

	Transform();

	void SetLocation(glm::vec3& pLocation);
	void SetRotation(glm::vec3& pRotation);
	void SetScale(glm::vec3& pScale);

	glm::mat4& GetModelMatrix();
	glm::mat4& GetNormalMatrix();

	std::vector<Property> GetProperties() override;

private:
	bool needsUpdate = false;
	
	glm::mat4 model;
	glm::mat4 normalMat;
	void UpdateModel();
};

