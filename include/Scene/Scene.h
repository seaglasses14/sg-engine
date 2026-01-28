#pragma once

#include "Camera.h"
#include "Core/Objects/GObject.h"
#include <shader.h>
#include <Material.h>
#include <object.h>
#include <Shapes.h>

struct FrameBufferIDs
{
	unsigned int fbo = 0;
	unsigned int texture = 0;
	unsigned int rbo = 0;
};

class Scene
{
public:
	Camera* mainCamera = nullptr;
	std::vector<GObject*> objects;
	Scene();

	void PreRender();
	void FirstPass();
	void SecondPass();

	void AddObject(const std::string& name);

	FrameBufferIDs fbIDs;

	Shader baseVertex;
	Material whiteMaterial;
	Object worldGrid;

private:
	std::string GenerateUniqueLabel(const std::string& name);
};

