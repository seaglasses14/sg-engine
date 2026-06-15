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
	AssetID id = "";
};

class AssetManager
{
public:
	std::string shader_desc_directory = "assets/descriptors/shaders/";
	std::string material_desc_directory = "assets/descriptors/materials/";
	std::string model_desc_directory = "assets/descriptors/basic_shapes/";
	std::string shader_raw_directory = "assets/raw/shaders/";

	static AssetManager& Get();

	Shader* GetShader(const AssetHandle<Shader>& handle);
	Material* GetMaterial(const AssetHandle<Material>& handle);
	Model* GetModel(const AssetHandle<Model>& handle);

	AssetManager(const AssetManager&) = delete;
	AssetManager& operator=(const AssetManager&) = delete;

protected:
	bool PrecompileShaders();
	bool PrecompileShaders(std::string directory);
	bool GenerateMaterials();
	bool GenerateMaterials(std::string directory);
	bool GenerateBaseModels();
	bool GenerateBaseModels(std::string directory);
	std::unordered_map<AssetID, Shader> shaders;
	std::unordered_map<AssetID, Material> materials;
	std::unordered_map<AssetID, Model> models;

private:
	AssetManager();
	void Init();
};