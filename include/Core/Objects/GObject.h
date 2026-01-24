#pragma once

#include <vector>

class Component;

class GObject
{
public:
	std::vector<Component*> components;
	GObject();
};

