#pragma once

#include "Core/Objects/Components/Property.h"

class GUI_PropertyHelper
{
public:
	static void DrawWidget(Property& pr);
private:
	static void WidgetBool(Property& pr);
	static void WidgetVec3f(Property& pr);
	static void WidgetColor(Property& pr);
	static void WidgetAssetHandleModel(Property& pr);
};