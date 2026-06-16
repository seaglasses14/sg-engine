#pragma once

#include "Data/Shader.h"
#include "Utility/DataTypes.h"
#include "Core/AssetPipeline/AssetManager.h"

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
	Material(AssetHandle<Shader> pShaderHandle);
	void AddUniform(const std::string& name, UniformValue value);
	bool ChangeUniform(const std::string& name, UniformValue value);
	void ChangeUniformMVP(glm::mat4& pModel, glm::mat4& pView, glm::mat4& pProjection);
	Shader& GetShader();
	void Activate(bool useShader = true);

private:
	AssetHandle<Shader> shaderHandle;
	Shader* cached_shader = nullptr;
	std::unordered_map<std::string, UniformValue> uniforms;
	void ApplyShader();
	void ApplyUniforms();
};