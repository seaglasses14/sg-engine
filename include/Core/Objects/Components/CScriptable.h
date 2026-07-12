#pragma once

#include "Core/Objects/Components/Component.h"

class CScriptable : public Component
{
public:
    virtual void Begin();

    virtual void Update(float deltaTime);

    virtual std::vector<Property> GetProperties() = 0;

protected:
};