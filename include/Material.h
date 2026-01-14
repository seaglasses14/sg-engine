#pragma once

#include "shader.h"
#include "texture.h"
#include "glm/glm.hpp"

#include <variant>
#include <string>

using UniformValue = std::variant<
	bool,
	int,
	float,
	glm::vec2,
	glm::vec3,
	glm::vec4,
	glm::mat3,
	glm::mat4
>;

class Material
{
public:
	Material(Shader* pShader, Texture* pTexture);
	void AddUniform(const std::string& name, UniformValue value);
	bool ChangeUniform(const std::string& name, UniformValue value);
	void SetShaderMVP(glm::mat4& pModel, glm::mat4& pView, glm::mat4& pProjection);
	void ApplyShader();
	void Activate(bool useShader);
	ShaderType GetShaderType();

private:
	Shader* shader;
	Texture* texture;
	glm::vec3 color;
	std::unordered_map<std::string, UniformValue> uniforms;
	void ApplyUniforms();
	void ApplyTexture();
};