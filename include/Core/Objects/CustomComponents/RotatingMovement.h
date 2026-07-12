#pragma once

#include "Core/Objects/Components/CScriptable.h"
#include "glm/glm.hpp"

class RotatingMovement : public CScriptable
{
public:
    RotatingMovement();

    void Begin() override;
    void Update(float deltaTime) override;

    std::vector<Property> GetProperties() override;

    glm::vec3 rotationCentre = glm::vec3();
    float speed = 1.0f;
    float radius = 3.0f;
};