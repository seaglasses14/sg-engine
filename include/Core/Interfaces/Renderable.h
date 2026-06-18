#pragma once

#include "Utility/DataTypes.h"

// Interface for Components
class IRenderable
{
public:
	virtual void Draw(RenderContext context) = 0;
	virtual bool IsVisible() = 0;
};