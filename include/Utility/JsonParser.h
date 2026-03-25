#pragma once

#include "json/json.hpp"
#include <string>
#include <iostream>
#include <fstream>
#include <filesystem>
#include "Core/Log.h"

namespace fs = std::filesystem;

static class JsonPaser
{
public:
	static ShaderDescriptor LoadShaderDescriptor(const fs::path& path)
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

			descriptor.vertex = json.value("vertex", "");
			descriptor.fragment = json.value("fragment", "");
			descriptor.fragment = json.value("geometry", "");

			if (descriptor.vertex == "" || descriptor.fragment == "")
			{
				LOG_ERROR("JsonPasers::Shader descriptor must have defined vertex and fragment paths");
			}
		}
		catch (std::ifstream::failure e)
		{
			LOG_ERROR("JsonPasers::Error when reading shader descriptor file");
		}
		
		return descriptor;
	}
};

class ShaderDescriptor
{
public:
	std::string vertex;
	std::string fragment;
	std::string geometry;
};
