#include "GObject.h"
#include "Core/Objects/Components/Transform.h"

GObject::GObject()
{
	Transform* comp = new Transform();
	components.push_back(comp);
}
