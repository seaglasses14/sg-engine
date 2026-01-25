#pragma once

#include <vector>
#include <string>

class Component;

class GObject
{
public:
	std::vector<Component*> components;
	std::string label;
	GObject(std::string pLabel);
};