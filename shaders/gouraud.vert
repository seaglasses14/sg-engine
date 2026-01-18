#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;

struct Material
{
	sampler2D diffuse;
	vec3 specular;
	float shininess;
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

out vec4 Color;

void main()
{
	// vertex position

	vec3 FragPos = vec3(model * vec4(aPos, 1.0));
	vec3 Normal = mat3(normalMat) * aNormal;
	vec2 TexCoord = aTexCoord;
	gl_Position = projection * view * vec4(FragPos, 1.0);

	// light calculations
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(light.position - FragPos);
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);

	// diffuse
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = (diff * vec3(texture(material.diffuse, TexCoord))) * light.color;

	// ambient
	float ambientStrength = 0.2;
	vec3 ambient = diffuse * ambientStrength * light.color;

	// specular
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	vec3 specular = (spec * material.specular) * light.color;

	// result
	vec3 result = ambient + diffuse + specular;

	Color = vec4(result, 1.0);
}