#include "CLight.h"
#include "Core/Objects/GObject.h"
#include "Scene/Scene.h"

CLight::CLight()
{
    label = "Light";
}

std::vector<Property> CLight::GetProperties()
{
    return
    {
        { PropertyType::Color, &color, "Color", [](){} },
        { PropertyType::Bool, &isEnabled, "IsEnabled", [this](){ SetEnabled(isEnabled); } }
    };
}

bool CLight::SetEnabled(bool enable)
{
    if(enable)
    {
        isEnabled = enable;
    }
    else
    {
        isEnabled = enable;
    }
    return isEnabled;
}