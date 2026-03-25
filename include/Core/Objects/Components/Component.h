#pragma once

//#include "Core/Objects/GObject.h"
#include <vector>
#include "Core/Objects/Components/Property.h"
#include "Core/Interfaces/MemoryManaged.h"

class GObject;

class Component : IMemoryManaged
{
public:
	virtual std::vector<Property> GetProperties() = 0;
	std::string label;
	// Destroy method implementation is not mandatory
	void Destroy() override {};
protected:
	GObject* owner = nullptr;
};

