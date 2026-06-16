#pragma once

#include "Core/Objects/Components/Property.h"

class GUI_PropertyHelper
{
public:
	static void DrawWidget(Property& pr);
private:
	static void WidgetVec3f(Property& pr);
	static void WidgetAssetHandle(Property& pr);
};