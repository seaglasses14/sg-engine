#pragma once

#include "Material.h"
#include "texture.h"
#include <glm/glm.hpp>

class Object
{
public:
    Object(unsigned int pVAO, unsigned int pVBO, unsigned int pEBO, Material* pMaterial, bool pUseEBO, int pIndicesSize);
	void Activate(glm::mat4& pView, glm::mat4& pProjection, bool useShader = true);
    void Draw();
    void Clean();
    ShaderType GetShaderType();
private:
    glm::mat4 model;
    bool useEBO;
    Material* material;
    int indicesSize;
	unsigned int VAO = 0, VBO = 0, EBO = 0;
};