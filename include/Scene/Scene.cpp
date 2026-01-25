#include "Scene.h"

Scene::Scene()
{
	objects = std::vector<GObject*>();
	objects.push_back(new GObject("Object1"));
	objects.push_back(new GObject("Object2"));
}
