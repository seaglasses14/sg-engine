#pragma once

//#include "Core/Objects/GObject.h"
#include <vector>
#include "Core/Objects/Components/Property.h"

class GObject;

class Component
{
public:
	virtual std::vector<Property> GetProperties() = 0;
	std::string label;
protected:
	GObject* owner = nullptr;
};

