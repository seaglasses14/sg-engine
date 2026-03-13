#pragma once

#include <vector>
#include <string>

class Component;
class Transform;

class GObject
{
public:
	Transform* transform;
	std::vector<Component*> components;
	std::string label;
	GObject(std::string pLabel);
};