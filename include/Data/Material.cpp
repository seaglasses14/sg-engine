#pragma once

#include "Material.h"

constexpr auto UNIFORM_MODEL = "model";
constexpr auto UNIFORM_VIEW = "view";
constexpr auto UNIFORM_PROJECTION = "projection";

Material::Material(Shader* pShader)
    : shader(pShader) { }

void Material::AddUniform(const std::string& name, UniformValue value)
{
    uniforms[name] = value;
}

bool Material::ChangeUniform(const std::string& name, UniformValue value)
{
    if (uniforms.contains(name))
    {
        uniforms[name] = value;
        return true;
    }
    return false;
}

void Material::ChangeUniformMVP(glm::mat4& pModel, glm::mat4& pView, glm::mat4& pProjection)
{
    uniforms[UNIFORM_MODEL] = pModel;
    uniforms[UNIFORM_VIEW] = pView;
    uniforms[UNIFORM_PROJECTION] = pProjection;
}

void Material::ApplyUniforms()
{
    for (auto& [name, value] : uniforms)
    {
        std::visit([&](auto&& v) { shader->set(name, v); }, value);
    }
}

void Material::ApplyShader()
{
    shader->use();
}

void Material::Activate(bool useShader)
{
    if (useShader)
        ApplyShader();
    ApplyUniforms();
}