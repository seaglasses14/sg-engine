#include "AssetManager.h"
#include <iostream>
#include <filesystem>
#include "Utility/JsonParser.h"

namespace fs = std::filesystem;

Shader* AssetManager::GetShader(const AssetHandle<Shader>& handle)
{
    shaders.find(handle.id);
    if (item != shaders.end())
    {
        shaders.at(handle.it)
    }
    return nullptr;
}

bool AssetManager::PrecompileShaders()
{
    for (const auto& entry : fs::directory_iterator(shader_desc_directory))
    {
        fs::path path = entry.path();
        if (entry.is_directory())
        {
            // check what kind of path to use for PrecompileShaders()
            PrecompileShaders(path.string());
        }
        if (path.has_extension())
        {
            if (path.extension().string() == "json")
            {
                ShaderDescriptor desc = JsonPaser::LoadShaderDescriptor(entry.path());
            }
        }
    }

    return true;
}

bool AssetManager::PrecompileShaders(std::string directory)
{
    for (const auto& entry : fs::directory_iterator(directory))
    {
        if (entry.is_directory())
        {
            PrecompileShaders();
        }
    }
    return true;
}