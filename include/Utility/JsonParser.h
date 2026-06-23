#pragma once

#include "json/json.hpp"
#include <string>
#include <vector>
#include <filesystem>

#include "Data/Material.h"

namespace fs = std::filesystem;

struct UniformStruct
{
	std::string name;
	UniformValue value;
};

struct TextureStruct
{
	std::string type;
	std::string textureHandle;
};

struct ModelMaterialStruct
{
	unsigned int slot = 0;
	std::string materialHandle;
};

// Could change to struct

class ShaderDescriptor
{
public:
	bool isValid = true;

	std::string assetID;
	std::string vertex;
	std::string fragment;
	std::string geometry;
};

class MaterialDescriptor
{
public:
	bool isValid = true;

	std::string assetID;
	std::string shaderHandle;
	std::vector<TextureStruct> textures;
	std::vector<UniformStruct> uniforms;
};

class ModelDescriptor
{
public:
	bool isValid = true;

	std::string assetID;
	std::string mesh;
	std::vector<ModelMaterialStruct> materials;
};

class JsonParser
{
public:
	static ShaderDescriptor LoadShaderDescriptor(const fs::path& path);
	static MaterialDescriptor LoadMaterialDescriptor(const fs::path& path);
	static ModelDescriptor LoadModelDescriptor(const fs::path& path);

	static UniformValue ParseUniform(const nlohmann::json& u);
};