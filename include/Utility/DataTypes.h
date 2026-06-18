#pragma once
#include <glm/glm.hpp>

struct RenderContext
{
	// Window data
	glm::mat4 projection;

	// Camera data
	glm::mat4 view;

	// Scene lights
	glm::vec3 directLight_direction;
	glm::vec3 directLight_color;
};