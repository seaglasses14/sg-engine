#pragma once


#include "Data/Material.h"
#include <glm/glm.hpp>

class Object
{
public:
    Object(unsigned int pVAO, unsigned int pVBO, unsigned int pEBO, Material* pMaterial, bool pTraingleMode, bool pUseEBO, int pIndicesSize);
	void Activate(glm::mat4& pView, glm::mat4& pProjection, bool useShader = true);
    void SetModel(glm::mat4& pModel);
    void Draw();
    void Clean();
private:
    bool triangleMode;
    glm::mat4 model;
    bool useEBO;
    Material* material;
    int indicesSize;
	unsigned int VAO = 0, VBO = 0, EBO = 0;
};
