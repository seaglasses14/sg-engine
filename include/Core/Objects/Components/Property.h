#pragma once

#include <string>
#include <functional>

enum PropertyType
{
	Int,
	Float,
	Vec3f,
	Asset
};

struct Property
{
	PropertyType type;
	void* data;
	std::string label;
	std::function<void()> onChanged;
};