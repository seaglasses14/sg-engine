#pragma once

class Texture
{
public:
	//32 Max number of Textures per Object
	//Could change
	unsigned int IDs[32];

	Texture(const char* texturePath[], const int nrTextures);
	Texture(const char* texturePath);
	void ActivateAll();

private:
	int IDsSize;
};