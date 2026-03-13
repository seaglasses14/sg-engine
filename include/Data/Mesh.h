#pragma once

#include "Core/Objects/Components/Component.h"
#include "glm/glm.hpp"
#include <string>
#include <vector>
#include "Data/Shader.h"

constexpr auto TX_TYPE_DIFFUSE = "texture_diffuse";
constexpr auto TX_TYPE_SPECULAR = "texture_specular";
constexpr auto TX_TYPE_NORMAL = "texture_normal";
constexpr auto TX_TYPE_HEIGHT = "texture_height";


struct Vertex
{
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;

	// Future Support
	glm::vec3 Tangent;
	glm::vec3 Bitangent;
	// int m_BoneIDs[MAX_BONE_INFLUENCE];
	// float m_Weights[MAX_BONE_INFLUENCE];
};

struct Texture
{
	unsigned int id = 0;
	std::string type; // Use TX_TYPE_ const expressions
	std::string path;
};

class Mesh
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