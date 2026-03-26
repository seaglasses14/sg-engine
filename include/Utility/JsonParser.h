#pragma once

#include "json/json.hpp"
#include <string>
#include <vector>
#include <filesystem>
#include "Data/Material.h"

namespace fs = std::filesystem;

static class JsonParser
{
public:
	static ShaderDescriptor LoadShaderDescriptor(const fs::path& path);
	static MaterialDescriptor LoadMaterialDescriptor(const fs::path& path);
	
	static UniformValue ParseUniform(const nlohmann::json& u);
};

// Could change to struct
class ShaderDescriptor
{
public:
	bool isValid;

	std::string assetID;
	std::string vertex;
	std::string fragment;
	std::string geometry;
};

class MaterialDescriptor
{
public:
	bool isValid;

	std::string assetID;
	std::string shaderHandle;
	std::vector<UniformStruct> uniforms;
};

struct UniformStruct
{
	std::string name;
	UniformValue value;
};
