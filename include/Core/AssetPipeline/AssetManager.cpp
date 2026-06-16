#include "AssetManager.h"
#include <iostream>
#include <filesystem>
#include "Utility/JsonParser.h"
#include "Data/Shader.h"
//#include "Data/Material.h"
#include "Data/Model.h"
#include "Core/Log.h"

namespace fs = std::filesystem;

AssetManager& AssetManager::Get()
{
    static AssetManager instance;
    return instance;
}

AssetManager::AssetManager()
{
}

void AssetManager::Init()
{
    if (!PrecompileShaders())
        LOG_ERROR("AssetManager::Errors when precompiling shaders");
    if (!GenerateMaterials())
        LOG_ERROR("AssetManager::Errors when generating materials");
    if (!GenerateBaseModels())
        LOG_ERROR("AssetManager::Errors when generating models");
}

Shader* AssetManager::GetShader(const AssetHandle<Shader>& handle)
{
    if (shaders.find(handle.id) != shaders.end())
    {
        return &shaders.at(handle.id);
    }
    return nullptr;
}

Material* AssetManager::GetMaterial(const AssetHandle<Material>& handle)
{
    if (materials.find(handle.id) != materials.end())
    {
        return &materials.at(handle.id);
    }
    return nullptr;
}

Model* AssetManager::GetModel(const AssetHandle<Model>& handle)
{
    LOG_INFO(handle.id);
    for (auto& [key, value] : models)
    {
        LOG_INFO(key);
        if (key == handle.id)
            LOG_INFO("YAY");
    }
    if (models.find(handle.id) != models.end())
    {
        return &models.at(handle.id);
    }
    return nullptr;
}

bool AssetManager::PrecompileShaders()
{
    return PrecompileShaders(shader_desc_directory);
}

bool AssetManager::PrecompileShaders(std::string directory)
{
    for (const auto& entry : fs::directory_iterator(directory))
    {
        fs::path path = entry.path();
        if (entry.is_directory())
        {
            PrecompileShaders(path.string());
        }
        if (path.has_extension())
        {
            if (path.extension().string() == ".json")
            {
                ShaderDescriptor desc = JsonParser::LoadShaderDescriptor(entry.path());
                
                if (desc.isValid)
                {
                    if (desc.geometry == "")
                        shaders.insert({ desc.assetID, Shader(desc.vertex.c_str(), desc.fragment.c_str()) });
                    else
                        shaders.insert({ desc.assetID, Shader(desc.vertex.c_str(), desc.fragment.c_str(), desc.geometry.c_str()) });
                }
            }
        }
    }
    return true;
}

bool AssetManager::GenerateMaterials()
{
    return GenerateMaterials(material_desc_directory);
}

bool AssetManager::GenerateMaterials(std::string directory)
{
    for (const auto& entry : fs::directory_iterator(directory))
    {
        fs::path path = entry.path();
        if (entry.is_directory())
        {
            GenerateMaterials(path.string());
        }
        if (path.has_extension())
        {
            if (path.extension().string() == ".json")
            {
                MaterialDescriptor desc = JsonParser::LoadMaterialDescriptor(entry.path());

                if (desc.isValid)
                {
                    AssetHandle<Shader> shader_handle;
                    shader_handle.id = desc.shaderHandle;
                    Material material(shader_handle);
                    for (UniformStruct uniform : desc.uniforms)
                    {
                        material.AddUniform(uniform.name, uniform.value);
                    }
                    materials.insert({ desc.assetID, material });
                }
            }
        }
    }
    return true;
}

bool AssetManager::GenerateBaseModels()
{
    return GenerateBaseModels(model_raw_directory);
}

bool AssetManager::GenerateBaseModels(std::string directory)
{
    for (const auto& entry : fs::directory_iterator(directory))
    {
        fs::path path = entry.path();
        if (entry.is_directory())
        {
            GenerateBaseModels(path.string());
        }
        if (path.has_extension())
        {
            if (path.extension().string() == ".obj")
            {
                Model model = Model(entry.path().string().c_str());

                models.insert({ entry.path().string(), model });
            }
        }
    }
    return true;
}
