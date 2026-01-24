#pragma once

#include <string>

enum PropertyType
{
	Int,
	Float,
	Vec3f
};

struct Property
{
	PropertyType type;
	void* data;
	std::string label;
};