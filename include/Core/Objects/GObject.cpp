#include "GObject.h"
#include "Core/Objects/Components/Transform.h"
#include "Core/Log.h"

GObject::GObject(std::string pLabel)
{
	transform = new Transform();
	components.push_back(transform);
	label = pLabel;
}
