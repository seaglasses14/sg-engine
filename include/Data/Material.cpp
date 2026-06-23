#pragma once

#include "Material.h"

constexpr auto UNIFORM_MODEL = "model";
constexpr auto UNIFORM_VIEW = "view";
constexpr auto UNIFORM_PROJECTION = "projection";
constexpr auto UNIFORM_NORMAL_MODEL = "normalMat";

Material::Material(AssetHandle<Shader> pShaderHandle)
    : shaderHandle(pShaderHandle)
{
    cached_shader = AssetManager::Get().GetShader(shaderHandle);
}

void Material::AddUniform(const std::string& name, UniformValue value)
{
    uniforms[name] = value;
}

void Material::AddTexture(const std::string &type, AssetHandle<Texture> handle)
{
    AssetData<Texture> data;
    data.handle = handle;
    data.cached_texture = AssetManager::Get().GetTexture(handle);
    textures[type] = data;
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

void Material::ChangeUniformMVP(glm::mat4& pModel, glm::mat4& pView, glm::mat4& pProjection, glm::mat4& pNormalMat)
{
    uniforms[UNIFORM_MODEL] = pModel;
    uniforms[UNIFORM_VIEW] = pView;
    uniforms[UNIFORM_PROJECTION] = pProjection;
    uniforms[UNIFORM_NORMAL_MODEL] = pNormalMat;
}

void Material::InitTexSlots()
{
    for (auto& [name, value] : textures)
    {
        cached_shader->set(name, GetTextureUnit(name.c_str()));
    }
}

Shader& Material::GetShader()
{
    return *cached_shader;
}

void Material::ApplyUniforms()
{
    for (auto& [name, value] : uniforms)
    {
        std::visit([&](auto&& v)
            {cached_shader->set(name, v); 
            }, value);
    }
}

void Material::ApplyShader()
{
    cached_shader->use();
}

void Material::ApplyTextures()
{
    for (auto& [type, value] : textures)
    {
        glActiveTexture(GL_TEXTURE0 + GetTextureUnit(type.c_str()));
        glBindTexture(GL_TEXTURE_2D, value.cached_texture->id);
    }
}

void Material::Activate(bool useShader)
{
    if (useShader)
        ApplyShader();
    ApplyTextures();
    ApplyUniforms();
}