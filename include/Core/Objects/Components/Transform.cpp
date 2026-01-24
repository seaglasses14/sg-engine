#include "Transform.h"

#include <glm/gtc/matrix_transform.hpp>

Transform::Transform()
{
	location = glm::vec3(0, 0, 0);
	rotation = glm::vec3(0, 0, 0);
	scale = glm::vec3(1, 1, 1);

	label = "Transform";

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

std::vector<Property> Transform::GetProperties()
{
	return
	{
		{ PropertyType::Vec3f, &location, "Location" },
		{ PropertyType::Vec3f, &rotation, "Rotation" },
		{ PropertyType::Vec3f, &scale, "Scale" }
	};
}

void Transform::UpdateModel()
{
	glm::mat4 newModel = glm::mat4(1.f);
	newModel = glm::scale(newModel, scale);
	newModel = glm::rotate(newModel, rotation.x, { 1.f, 0.f, 0.f });
	newModel = glm::rotate(newModel, rotation.y, { 0.f, 1.f, 0.f });
	newModel = glm::rotate(newModel, rotation.z, { 0.f, 0.f, 1.f });
	model = glm::translate(newModel, location);
}
