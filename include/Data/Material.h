#pragma once

#include "Data/Shader.h"
#include "Utility/DataTypes.h"
#include "Core/AssetPipeline/AssetManager.h"

#include <variant>
#include <string>

constexpr auto TX_TYPE_DIFFUSE = "material.diffuse";
constexpr auto TX_TYPE_SPECULAR = "material.specular";
constexpr auto TX_TYPE_NORMAL = "material.normal";
constexpr auto TX_TYPE_HEIGHT = "material.height";
constexpr auto TX_TYPE_EMISSIVE = "material.emissive";

constexpr int TX_UNIT_DIFFUSE = 0;
constexpr int TX_UNIT_SPECULAR = 1;
constexpr int TX_UNIT_NORMAL = 2;
constexpr int TX_UNIT_HEIGHT = 3;
constexpr int TX_UNIT_EMISSIVE = 4;

constexpr int GetTextureUnit(const char* tx_type)
{
	if (tx_type == TX_TYPE_DIFFUSE) return TX_UNIT_DIFFUSE;
    if (tx_type == TX_TYPE_SPECULAR) return TX_UNIT_SPECULAR;
	if (tx_type == TX_TYPE_NORMAL) return TX_UNIT_NORMAL;
	if (tx_type == TX_TYPE_HEIGHT) return TX_UNIT_HEIGHT;
	if (tx_type == TX_TYPE_EMISSIVE) return TX_UNIT_EMISSIVE;

    return 0;
}

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

struct Texture
{
	unsigned int id = 0;
	std::string type; // Use TX_TYPE_ const expressions
	std::string path;
};

template<typename T>
struct AssetData
{
	AssetHandle<T> handle;
	T* cached_texture;
};

class Material
{	
public:
	Material(AssetHandle<Shader> pShaderHandle);
	void AddUniform(const std::string& name, UniformValue value);
	void AddTexture(const std::string& type, AssetHandle<Texture> handle);
	bool ChangeUniform(const std::string& name, UniformValue value);
	void ChangeUniformMVP(glm::mat4& pModel, glm::mat4& pView, glm::mat4& pProjection, glm::mat4& pNormalMat);
	void InitTexSlots();
	Shader& GetShader();
	void Activate(bool useShader = true);

private:
	AssetHandle<Shader> shaderHandle;
	Shader* cached_shader = nullptr;
	std::unordered_map<std::string, AssetData<Texture>> textures;
	std::unordered_map<std::string, UniformValue> uniforms;

	void ApplyShader();
	void ApplyTextures();
	void ApplyUniforms();
};