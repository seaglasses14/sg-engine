#pragma once

#include "Camera.h"
#include "Core/Objects/GObject.h"
//#include <shader.h>
//#include <Material.h>
#include <object.h>
#include "Utility/ObjectFactory.h"
#include "Core/Objects/Light.h"

struct FrameBuffer
{
	unsigned int fbo = 0;
	unsigned int tex = 0;
	unsigned int rbo = 0;
	
	int width = 800;
	int height = 600;
};

class Scene
{
public:
	Camera* mainCamera = nullptr;
	std::vector<GObject*> objects;
	std::vector<Light*> lights;
	Scene();

	Object* worldGrid;

	void PreRender();
	void FirstPass();
	void SecondPass();

	void Init();

	void AddObject(const std::string& name);

	FrameBuffer fb;

private:
	std::string GenerateUniqueLabel(const std::string& name);
	void BindFrameBuffer() const;
	void UnbindFrameBuffer();
	void GenerateFrameBuffer();
	void ResizeFrameBuffer();
};