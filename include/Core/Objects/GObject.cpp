#include "GObject.h"
#include "Core/Objects/Components/Transform.h"
#include "Core/Log.h"

GObject::GObject(std::string pLabel)
{
	Transform* comp = new Transform();
	components.push_back(comp);
	label = pLabel;
}
