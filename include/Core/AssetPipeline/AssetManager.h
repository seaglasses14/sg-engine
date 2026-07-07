#pragma once

#include <string>
#include <unordered_map>
#include <vector>
#include "Utility/DataTypes.h"

class Shader;
class Texture;
class Material;
class Model;

class AssetManager
{
public:
	std::string shader_desc_directory = "assets/descriptors/shaders/";
	std::string material_desc_directory = "assets/descriptors/materials/";
	std::string model_raw_directory = "assets/raw/models/";
	std::string texture_raw_directory = "assets/raw/textures/";
	std::string shader_raw_directory = "assets/raw/shaders/";

	static AssetManager& Get();

	void Init();

	Shader* GetShader(const AssetHandle<Shader>& handle);
	Texture* GetTexture(const AssetHandle<Texture>& handle);
	Material* GetMaterial(const AssetHandle<Material>& handle);
	Model* GetModel(const AssetHandle<Model>& handle);

	std::vector<AssetID>& GetShaderAssetIDs();
	std::vector<AssetID>& GetTextureAssetIDs();
	std::vector<AssetID>& GetMaterialAssetIDs();
	std::vector<AssetID>& GetModelAssetIDs();

	AssetManager(const AssetManager&) = delete;
	AssetManager& operator=(const AssetManager&) = delete;

protected:
	bool PrecompileShaders();
	bool PrecompileShaders(std::string directory);
	bool GenerateTextures();
	bool GenerateTextures(std::string directory);
	bool GenerateMaterials();
	bool GenerateMaterials(std::string directory);
	bool GenerateBaseModels();
	bool GenerateBaseModels(std::string directory);
	
	std::unordered_map<AssetID, Shader> shaders;
	std::vector<AssetID> shader_ids;

	std::unordered_map<AssetID, Texture> textures;
	std::vector<AssetID> texture_ids;

	std::unordered_map<AssetID, Material> materials;
	std::vector<AssetID> material_ids;

	std::unordered_map<AssetID, Model> models;
	std::vector<AssetID> model_ids;

private:
	AssetManager();
};