#pragma once

#include <string>
#include <functional>

enum PropertyType
{
	Bool,
	Int,
	Float,
	Vec3f,
	Color,
	AssetHandle_Model,
	AssetHandle_Material
};

struct Property
{
	PropertyType type;
	void* data;
	std::string label;
	std::function<void()> onChanged;
};