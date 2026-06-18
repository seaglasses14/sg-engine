#pragma once

#include "Camera.h"
#include "Core/Objects/GObject.h"
//#include <shader.h>
//#include <Material.h>
#include <object.h>
#include "Utility/ObjectFactory.h"
//#include "Core/Objects/Components/DirectLight.h"

class CDirectLight;

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
	//std::vector<Light*> lights;
	CDirectLight* directLight = nullptr;
	Scene();

	Object* worldGrid;

	void PreRender();
	void FirstPass();
	void SecondPass();

	void Init();

	GObject* CreateEmpty(const std::string& name);
	GObject* CreateCube(const std::string& name);
	GObject* CreateDirectLight(const std::string& name);
	std::string SetObjectLabel(GObject* obj, const std::string& name);

	FrameBuffer fb;

private:
	GObject* AddObject(GObject* obj);
	std::string GenerateUniqueLabel(const std::string& name, GObject* currentObj = nullptr);
	void BindFrameBuffer() const;
	void UnbindFrameBuffer();
	void GenerateFrameBuffer();
	void ResizeFrameBuffer();
};