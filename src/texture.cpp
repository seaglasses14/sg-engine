#include "texture.h"
#include "log.h"

#include <stb_image/stb_image.h>
#include <glad/glad.h>

Texture::Texture(const char* texturePath[], const int nrTextures)
{
	//This constructor accepts only pngs (or RGBA Formats), and has fixed texture parameters (wrapping e filtering)

	IDsSize = nrTextures;
	glGenTextures(IDsSize, IDs);

	stbi_set_flip_vertically_on_load(true);

	for (int i = 0; i < IDsSize; i++)
	{
		glBindTexture(GL_TEXTURE_2D, IDs[i]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		int width, height, nrChannels;

		unsigned char* data = stbi_load(texturePath[i], &width, &height, &nrChannels, 0);
		if (data)
		{
			if (nrChannels == 3)
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			else if (nrChannels == 4)
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
			else
				LOG_ERROR("Texture Error: Unsupported number of channels");
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else
		{
			LOG_ERROR("Texture Error : Failed to load texture");
		}
		stbi_image_free(data);
	}
}
Texture::Texture(const char* texturePath)
{
	//This constructor accepts only pngs (or RGBA Formats), and has fixed texture parameters (wrapping e filtering)

	IDsSize = 1;
	glGenTextures(IDsSize, IDs);

	stbi_set_flip_vertically_on_load(true);

	glBindTexture(GL_TEXTURE_2D, IDs[0]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	int width, height, nrChannels;

	unsigned char* data = stbi_load(texturePath, &width, &height, &nrChannels, 0);
	if (data)
	{
		if (nrChannels == 3)
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		else if (nrChannels == 4)
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		else
			LOG_ERROR("Texture Error: Unsupported number of channels");
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		LOG_ERROR("Texture Error : Failed to load texture");
	}
	stbi_image_free(data);
}
void Texture::ActivateAll()
{
	for (int i = 0; i < IDsSize; i++)
	{
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, IDs[i]);
	}
}