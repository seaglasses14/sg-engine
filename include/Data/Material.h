#pragma once

#include "Data/Shader.h"
#include "texture.h"

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
	Material(Shader* pShader);
	void AddUniform(const std::string& name, UniformValue value);
	bool ChangeUniform(const std::string& name, UniformValue value);
	void ChangeUniformMVP(glm::mat4& pModel, glm::mat4& pView, glm::mat4& pProjection);
	void Activate(bool useShader);

private:
	Shader* shader;
	std::unordered_map<std::string, UniformValue> uniforms;
	void ApplyShader();
	void ApplyUniforms();
};