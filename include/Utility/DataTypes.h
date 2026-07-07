#pragma once
#include <glm/glm.hpp>

using AssetID = std::string;

template<typename T>
struct AssetHandle
{
	AssetID id; //= ""
};

template<typename T>
struct AssetData
{
	AssetHandle<T> handle;
	T* cached_data = nullptr;
};

struct RenderContext
{
	// Window data
	glm::mat4 projection;

	// Camera data
	glm::mat4 view;

	// Scene lights
	glm::vec3 directLight_direction;
	glm::vec3 directLight_color;
};