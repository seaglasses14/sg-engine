#pragma once

#include "Core/Objects/Components/Component.h"
#include "glm/glm.hpp"

class CDirectLight: public Component
{
public:
	CDirectLight();

	std::vector<Property> GetProperties() override;

    bool SetEnabled(bool enable = true);

    glm::vec3 direction = glm::vec3(0.8f, -0.5f, -1.0f);
    glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f);

    //glm::vec3 GetDirection();
    //glm::vec3 GetColor();
    //glm::vec3 SetColor(glm::vec3& color);

private:
	bool isEnabled;
};