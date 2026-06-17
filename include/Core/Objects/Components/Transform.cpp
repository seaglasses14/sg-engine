#include "Transform.h"

#include <glm/gtc/matrix_transform.hpp>

Transform::Transform()
{
	location = glm::vec3(0, 0, 0);
	rotation = glm::vec3(0, 0, 0);
	scale = glm::vec3(1, 1, 1);

	label = "Transform";

	needsUpdate = true;
}

void Transform::SetLocation(glm::vec3& pLocation)
{
	location = pLocation;
	needsUpdate = true;
}

void Transform::SetRotation(glm::vec3& pRotation)
{
	rotation = pRotation;
	needsUpdate = true;
}

void Transform::SetScale(glm::vec3& pScale)
{
	scale = pScale;
	needsUpdate = true;
}

glm::mat4& Transform::GetModelMatrix()
{
	if (needsUpdate)
	{
		UpdateModel();
		needsUpdate = false;
	}
	return model;
}

glm::mat4 &Transform::GetNormalMatrix()
{
    if (needsUpdate)
	{
		UpdateModel();
		needsUpdate = false;
	}
	return normalMat;
}

std::vector<Property> Transform::GetProperties()
{
	return
	{
		{ PropertyType::Vec3f, &location, "Location",  [this](){ needsUpdate = true; }},
		{ PropertyType::Vec3f, &rotation, "Rotation", [this](){ needsUpdate = true; }},
		{ PropertyType::Vec3f, &scale, "Scale", [this](){ needsUpdate = true; } }
	};
}

void Transform::UpdateModel()
{
	glm::mat4 newModel = glm::mat4(1.f);
	newModel = glm::translate(newModel, location);
	newModel = glm::rotate(newModel, rotation.x, { 1.f, 0.f, 0.f });
	newModel = glm::rotate(newModel, rotation.y, { 0.f, 1.f, 0.f });
	newModel = glm::rotate(newModel, rotation.z, { 0.f, 0.f, 1.f });
	newModel = glm::scale(newModel, scale);
	model = newModel;
	normalMat = glm::transpose(glm::inverse(model));
}
