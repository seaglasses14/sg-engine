#pragma once

#include <vector>

class Texture
{
public:
	//32 Max number of Textures per Object
	//Could change
	unsigned int IDs[32];

	Texture(const std::vector<const char*>& texturePath);
	Texture(const char* texturePath);
	void ActivateAll();

private:
	int IDsSize;
};