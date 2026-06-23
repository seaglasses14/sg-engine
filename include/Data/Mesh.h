#pragma once

#include "Core/Objects/Components/Component.h"
#include "glm/glm.hpp"
#include <string>
#include <vector>
#include "Data/Shader.h"

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

class Mesh
{
public:
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	unsigned int materialSlot;

	//std::vector<Texture> textures;

	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, unsigned int materialSlot = 0);
	void Draw();

private:
	unsigned int VAO, VBO, EBO;
	void InitMesh();
};