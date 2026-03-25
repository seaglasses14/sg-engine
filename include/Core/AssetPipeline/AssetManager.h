#pragma once
#include <string>
#include <unordered_map>

class Shader;
class Material;
class Model;

using AssetID = std::string;

template<typename T>
struct AssetHandle
{
	AssetID id;
};

class AssetManager
{
public:
	std::string shader_desc_directory = "assets/descriptors/shaders/";
	std::string shader_raw_directory = "assets/raw/shaders/";

	AssetManager();
	bool Init();

	Shader* GetShader(const AssetHandle<Shader>& handle);

protected:
	bool PrecompileShaders();
	bool PrecompileShaders(std::string directory);
	std::unordered_map<AssetID, Shader> shaders;
};