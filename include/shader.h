#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <string>

enum ShaderType
{
	BaseST,
	TextureST
};

struct ShaderParams
{
	bool a;
};

class Shader
{
public:
	Shader(const char* vertexPath, const char* fragmentPath, ShaderType pShderType);
	void use();
	void set(const std::string& name, bool value) const;
	void set(const std::string& name, int value) const;
	void set(const std::string& name, float value) const;
	void set(const std::string& name, const glm::vec2& value) const;
	void set(const std::string& name, float x, float y) const;
	void set(const std::string& name, const glm::vec3& value) const;
	void set(const std::string& name, float x, float y, float z) const;
	void set(const std::string& name, const glm::vec4& value) const;
	void set(const std::string& name, float x, float y, float z, float w) const;
	void set(const std::string& name, const glm::mat2& mat) const;
	void set(const std::string& name, const glm::mat3& mat) const;
	void set(const std::string& name, const glm::mat4& mat) const;
	ShaderType getShaderType();

private:
	enum class ShaderErrorCodes
	{
		VERTEX,
		FRAGMENT,
		PROGRAM
	};

	unsigned int ID;
	ShaderType shaderType;
	void checkCompileErrors(unsigned int shader, ShaderErrorCodes code);
};