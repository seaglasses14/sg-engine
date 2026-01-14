#include "object.h"
#include "log.h"
#include <iostream>
#include <glad/glad.h>

Object::Object(unsigned int pVAO, unsigned int pVBO, unsigned int pEBO, Material* pMaterial, bool pUseEBO, int pIndicesSize)
	: material(pMaterial), model(glm::mat4(1.0f))
{
	VAO = pVAO;
	VBO = pVBO;
	EBO = pEBO;
	useEBO = pUseEBO;
	indicesSize = pIndicesSize;
}
void Object::Activate(glm::mat4& pView, glm::mat4& pProjection, bool useShader)
{
	if (!(material == nullptr))
	{
		material->Activate(useShader);
		material->SetShaderMVP(model, pView, pProjection);
	}

	glBindVertexArray(VAO);
}

void::Object::Draw()
{
	if (useEBO)
	{
		glDrawElements(GL_TRIANGLES, indicesSize, GL_UNSIGNED_INT, 0);
		std::cout << glGetError() << std::endl;
	}
		
	else
		glDrawArrays(GL_LINES, 0, indicesSize);
}
void Object::Clean()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	//glDeleteProgram(shader.ID);
	//glDeleteTextures(2, texture.IDs);
}

ShaderType Object::GetShaderType()
{
	return material->GetShaderType();
}