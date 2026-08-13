#include "AssetManager.h"
#include <iostream>
#include <filesystem>
#include "Utility/JsonParser.h"
#include "Data/Shader.h"
#include "Data/Material.h"
#include "Data/Model.h"
#include "Core/Log.h"
#include "stb_image/stb_image.h"

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
    if (!GenerateTextures())
        LOG_ERROR("AssetManager::Errors when generating textures"); 
    if (!GenerateMaterials())
        LOG_ERROR("AssetManager::Errors when generating materials");
    if (!GenerateBaseModels())
        LOG_ERROR("AssetManager::Errors when generating models");
}

Shader* AssetManager::GetShader(const AssetHandle<Shader>& handle)
{
    if (shaders.contains(handle.id))
    {
        return &shaders.at(handle.id);
    }
    return nullptr;
}

Texture* AssetManager::GetTexture(const AssetHandle<Texture>& handle)
{
    if (textures.contains(handle.id))
    {
        return &textures.at(handle.id);
    }
    return nullptr;
}

Material* AssetManager::GetMaterial(const AssetHandle<Material>& handle)
{
    if (materials.contains(handle.id))
    {
        return &materials.at(handle.id);
    }
    return nullptr;
}

Model* AssetManager::GetModel(const AssetHandle<Model>& handle)
{
    if (models.contains(handle.id))
    {
        return &models.at(handle.id);
    }
    return nullptr;
}

InputAction *AssetManager::GetInputAction(const AssetHandle<InputAction> &handle)
{
    if(actions.contains(handle.id))
    {
        return &actions.at(handle.id);
    }
    return nullptr;
}

std::vector<AssetID> &AssetManager::GetShaderAssetIDs()
{
    return shader_ids;
}

std::vector<AssetID> &AssetManager::GetTextureAssetIDs()
{
    return texture_ids;
}

std::vector<AssetID> &AssetManager::GetMaterialAssetIDs()
{
    return material_ids;
}

std::vector<AssetID> &AssetManager::GetModelAssetIDs()
{
    return model_ids;
}

std::vector<AssetID> &AssetManager::GetInputActionIDs()
{
    return action_ids;
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
                    shader_ids.push_back(desc.assetID);
                }
            }
        }
    }
    return true;
}

bool AssetManager::GenerateTextures()
{
    return GenerateTextures(texture_raw_directory);
}

bool AssetManager::GenerateTextures(std::string directory)
{
    for (const auto& entry : fs::directory_iterator(directory))
    {
        fs::path path = entry.path();
        if (entry.is_directory())
        {
            GenerateTextures(path.string());
        }
        if (path.has_extension())
        {
            if (path.extension().string() == ".jpg" || path.extension().string() == ".png")
            {
                // TODO: Add Texture descriptor to defiene wrapping and filtering parameters

                Texture tex;
                tex.path = entry.path().string();
                tex.type = TX_TYPE_DIFFUSE;

                glGenTextures(1, &tex.id);
                glBindTexture(GL_TEXTURE_2D, tex.id);

                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
                
                int width, height, nrChannels;

                unsigned char* data = stbi_load(entry.path().string().c_str(), &width, &height, &nrChannels, 0);
                if (data)
                {
                    if (nrChannels == 3)
                        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
                    else if (nrChannels == 4)
                        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
                    else
                        LOG_ERROR("Texture Error: Unsupported number of channels");
                    glGenerateMipmap(GL_TEXTURE_2D);
                }
                else
                {
                    LOG_ERROR("Failed to load texture");
                    stbi_image_free(data);
                    return false;
                }
                stbi_image_free(data);
                textures.insert({ entry.path().string() , tex });
                texture_ids.push_back(entry.path().string());
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
                    for(TextureStruct tex: desc.textures)
                    {
                        material.AddTexture(tex.type, AssetHandle<Texture>({ tex.textureHandle }));
                    }
                    for (UniformStruct uniform : desc.uniforms)
                    {
                        material.AddUniform(uniform.name, uniform.value);
                    }
                    materials.insert({ desc.assetID, material });
                    material_ids.push_back(desc.assetID);
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
                model_ids.push_back(entry.path().string());
            }
        }
    }
    return true;
}

bool AssetManager::GenerateInputActions()
{
    return GenerateInputActions(action_desc_directory);
}

bool AssetManager::GenerateInputActions(std::string directory)
{
    for (const auto& entry : fs::directory_iterator(directory))
    {
        fs::path path = entry.path();
        if (entry.is_directory())
        {
            GenerateInputActions(path.string());
        }
        if (path.has_extension())
        {
            if (path.extension().string() == ".json")
            {
                InputActionDescriptor desc = JsonParser::LoadInputActionDescriptor(entry.path());

                if (desc.isValid)
                {
                    InputAction inputAction(desc.actionID, desc.type);
                    actions.insert({ desc.assetID, inputAction });
                    action_ids.push_back(desc.assetID);
                }
            }
        }
    }
    return true;
}