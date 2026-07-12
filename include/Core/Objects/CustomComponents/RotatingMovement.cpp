#include "RotatingMovement.h"
#include "Core/Objects/GObject.h"
#include "Core/Objects/Components/Transform.h"
#include "GLFW/glfw3.h"

RotatingMovement::RotatingMovement()
{
    label = "Rotating Movement";
}

void RotatingMovement::Begin()
{
    rotationCentre = owner->transform->location;
}

void RotatingMovement::Update(float deltaTime)
{
    float x = rotationCentre.x + radius * glm::sin(speed * glfwGetTime());
    float y = rotationCentre.y + radius * glm::cos(speed * glfwGetTime());
    owner->transform->SetLocation(glm::vec3(x, y, rotationCentre.z));
}

std::vector<Property> RotatingMovement::GetProperties()
{
    return
    {
        { PropertyType::Float, &speed, "Speed", [](){} },
        { PropertyType::Float, &radius, "Radius", [](){} }
    };
}
