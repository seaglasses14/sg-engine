#version 330 core
in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoord;
in vec3 LightPos;

out vec4 FragColor;

struct Material
{
	//vec3 ambient;
	sampler2D diffuse1;
	sampler2D diffuse2;
	sampler2D diffuse3;
	sampler2D specular;
	float shininess;
};

struct DirectLight
{
	vec3 direction;
	vec3 color;
};

struct Light
{
	vec3 position;
	vec3 color;

	float constant;
	float linear;
	float quadratic;
};

uniform DirectLight directLight;
uniform Material material;
uniform Light light;

uniform mat4 view;
uniform vec3 viewPos;

void main()
{
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(LightPos - FragPos);
	//vec3 lightDir = normalize(-directLight.direction);
	vec3 viewDir = normalize(-FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);

	float distance = length(LightPos - FragPos);
	float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

	// diffuse
	float diff = max(dot(norm, lightDir), 0.0);
	
	vec3 daynight = vec3(texture(material.diffuse1, TexCoord));
	vec3 emissive = vec3(texture(material.diffuse2, TexCoord));

	vec3 diffuse = (diff * daynight ) * light.color;

	// ambient
	float ambientLightStrength = 0.2;
	vec3 ambient = diffuse * ambientLightStrength * light.color;

	// specular
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	vec3 specular = (spec * vec3(texture(material.specular, TexCoord))) * light.color;

	diffuse *= attenuation;
	specular *= attenuation;

	vec3 result = ambient + diffuse + specular + emissive;
	
	FragColor = vec4(result, 1.0);
}