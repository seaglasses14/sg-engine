#pragma once

#include "Camera.h"
#include "Core/Objects/GObject.h"

class Scene
{
public:
	Camera* mainCamera = nullptr;
	std::vector<GObject*> objects;
	Scene();
};

