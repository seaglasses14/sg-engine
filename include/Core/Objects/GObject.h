#pragma once

#include <vector>
#include <string>

class Scene;
class Component;
class Transform;

class GObject
{
public:
	Scene* scene;
	Transform* transform;
	std::vector<Component*> components;
	std::string label;
	GObject(const std::string& pLabel, Scene* scene);
	
	template<typename T>
	T* GetComponent()
	{
		for (Component* component : components)
		{
			if (T* result = dynamic_cast<T*>(component))
				return result;
		}
		return nullptr;
	}

	void Destroy();
};
