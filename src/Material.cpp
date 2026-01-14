#pragma once

#include "Material.h"

Material::Material(Shader* pShader, Texture* pTexture)
    : shader(pShader), texture(pTexture), color(glm::vec3(0.f, 0.f, 0.f)) { }

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

void Material::ApplyUniforms()
{
    for (auto& [name, value] : uniforms)
    {
        std::visit([&](auto&& v) { shader->set(name, v); }, value);
    }
}

void Material::SetShaderMVP(glm::mat4& pModel, glm::mat4& pView, glm::mat4& pProjection)
{
    shader->set("model", pModel);
    shader->set("view", pView);
    shader->set("projection", pProjection);
}

ShaderType Material::GetShaderType()
{
    return shader->getShaderType();
}

void Material::ApplyShader()
{
    shader->use();
}

void Material::ApplyTexture()
{
    if (!(texture == nullptr))
        texture->ActivateAll();
}

void Material::Activate(bool useShader)
{
    if (useShader)
        ApplyShader();
    ApplyUniforms();
    if (texture != nullptr)
        ApplyTexture();
}