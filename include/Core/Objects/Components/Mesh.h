#pragma once

#include "Core/Objects/Components/Component.h"
#include "glm/glm.hpp"
#include <string>
#include <vector>
#include <shader.h>

struct Vertex
{
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;
};

struct Texture
{
	unsigned int id;
	TextureType type;
};

enum TextureType
{
	DIFFUSE,
	SPECULAR
};

class Mesh : public Component
{
public:
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture> textures;
	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
	void Draw(Shader& shader);

private:
	unsigned int VAO, VBO, EBO;
	void InitMesh();
};