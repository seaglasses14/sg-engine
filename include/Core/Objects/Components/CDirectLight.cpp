#include "CDirectLight.h"
#include "Core/Objects/GObject.h"
#include "Scene/Scene.h"

CDirectLight::CDirectLight()
{
    label = "DirectLight";
}

std::vector<Property> CDirectLight::GetProperties()
{
    return
    {
        { PropertyType::Vec3f, &direction, "Direction", [](){} },
        { PropertyType::Color, &color, "Color", [](){} },
        { PropertyType::Bool, &isEnabled, "IsEnabled", [this](){ SetEnabled(isEnabled); } }
    };
}

bool CDirectLight::SetEnabled(bool enable)
{
    if(enable)
    {
        if(owner->scene->directLight)
            owner->scene->directLight->SetEnabled(false);
        isEnabled = enable;
        owner->scene->directLight = this;
    }
    else
    {
        owner->scene->directLight = nullptr;
        isEnabled = enable;
    }
    return isEnabled;
}