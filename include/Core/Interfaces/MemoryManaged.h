#pragma once

// Interface for Components
class IMemoryManaged
{
public:
	virtual void Destroy() = 0;
};