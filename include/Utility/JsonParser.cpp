#include "JsonParser.h"

#include <iostream>
#include <fstream>
#include "Core/Log.h"

ShaderDescriptor JsonParser::LoadShaderDescriptor(const fs::path& path)
{
	ShaderDescriptor descriptor;
	std::ifstream file;
	file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try
	{
		file.open(path);

		nlohmann::json json;
		file >> json;

		file.close();

		descriptor.isValid = true;
		descriptor.assetID = json.value("assetID", "");
		descriptor.vertex = json.value("vertex", "");
		descriptor.fragment = json.value("fragment", "");
		descriptor.geometry = json.value("geometry", "");

		if (descriptor.assetID == "", descriptor.vertex == "" || descriptor.fragment == "")
		{
			LOG_ERROR("JsonPasers::Shader descriptor must have defined asset id, vertex and fragment paths");
			descriptor.isValid = false;
		}
	}
	catch (std::ifstream::failure e)
	{
		LOG_ERROR("JsonPasers::Error when reading shader descriptor file");
		descriptor.isValid = false;
	}

	return descriptor;
}

MaterialDescriptor JsonParser::LoadMaterialDescriptor(const fs::path& path)
{
	MaterialDescriptor descriptor;

	std::ifstream file;
	file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try
	{
		file.open(path);

		nlohmann::json json;
		file >> json;

		file.close();

		descriptor.isValid = true;
		descriptor.assetID = json.value("assetID", "");
		descriptor.shaderHandle = json.value("shader_handle", "");

		if (json.contains("uniforms"))
		{
			for (auto& u : json["uniforms"])
			{
				UniformStruct uniform;
				uniform.name = u.at("name").get<std::string>();
				uniform.value = ParseUniform(u);
				descriptor.uniforms.push_back(uniform);
			}
		}

		if (descriptor.assetID == "", descriptor.shaderHandle == "")
		{
			LOG_ERROR("JsonPasers::Material descriptor must have defined asset id, shader_handle");
			descriptor.isValid = false;
		}
	}
	catch (std::ifstream::failure e)
	{
		LOG_ERROR("JsonPasers::Error when reading material descriptor file");
		descriptor.isValid = false;
	}

	return descriptor;
}

UniformValue JsonParser::ParseUniform(const nlohmann::json& u)
{
	std::string type = u.at("type").get<std::string>();
	const auto& value = u.at("value");
	if (type == "bool")
		return value.get<bool>();
	if (type == "int")
		return value.get<int>();
	if (type == "float")
		return value.get<float>();
	if (type == "vec2")
		return glm::vec2(
			value[0].get<float>(),
			value[1].get<float>());
	if (type == "vec3")
		return glm::vec3(
			value[0].get<float>(),
			value[1].get<float>(),
			value[2].get<float>());
	if (type == "vec4")
		return glm::vec4(
			value[0].get<float>(),
			value[1].get<float>(),
			value[2].get<float>(),
			value[3].get<float>());
	// To add Mat3 and Mat4 support
	throw std::runtime_error("Unsupported Uniform type: " + type);
}