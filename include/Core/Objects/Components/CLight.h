#pragma once

#include "Core/Objects/Components/Component.h"
#include "glm/glm.hpp"

class CLight: public Component
{
public:
	CLight();

	std::vector<Property> GetProperties() override;

    bool SetEnabled(bool enable = true);

    glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f);

private:
	bool isEnabled;
};