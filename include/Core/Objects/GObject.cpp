#include "GObject.h"

#include <utility>
#include "Core/Objects/Components/Transform.h"
#include "Core/Log.h"
#include "Scene/Scene.h"

GObject::GObject(const std::string& pLabel, Scene* scene)
{
	this->scene = scene;
	transform = new Transform();
	transform->owner = this;
	components.push_back(transform);
	label = pLabel;
}

void GObject::Destroy()
{
	for (Component* component : components)
	{
		component->Destroy();
	}
}