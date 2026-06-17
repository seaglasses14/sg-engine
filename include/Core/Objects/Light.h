#pragma once

#include "Core/Objects/GObject.h"

enum LightType
{
	Directional,
	Point,
	Spot
};

class Light : GObject
{

public:
	LightType type;

private:

};

