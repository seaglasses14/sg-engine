#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;

struct Material
{
	uniform vec3 diffuse;
	uniform vec3 specular;
	uniform float shininess;
};

struct Light
{
	vec3 position;
	vec3 color;
};

uniform Material material;
uniform Light light;

uniform vec3 viewPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform mat4 normalMat;

out vec3 Color;

void main()
{
	// vertex position

	FragPos = vec3(model * vec4(aPos, 1.0);
	Normal = mat3(normalMat) * aNormal;
	gl_Position = projection * view * vec4(FragPos, 1.0);

	// diffuse

	// ambient

	// speculare

	// result
	
}