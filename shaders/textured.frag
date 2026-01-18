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

struct Light
{
	vec3 position;
	vec3 color;
};

uniform Material material;
uniform Light light;

uniform mat4 view;
uniform vec3 viewPos;

void main()
{
	vec3 norm = normalize(Normal);
	//vec3 lightDir = normalize(light.Position - FragPos);
	vec3 lightDir = normalize(LightPos - FragPos);
	//vec3 viewDir = normalize(viewPos - FragPos);
	vec3 viewDir = normalize(-FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);

	// diffuse
	float diff = max(dot(norm, lightDir), 0.0);
	//vec4 daynight = mix(texture(material.diffuse1, TexCoord), texture(material.diffuse2, TexCoord), diff);
	vec4 daynight = texture(material.diffuse1, TexCoord);
	vec3 diffuse = (diff * ( vec3( mix(daynight , texture(material.diffuse3, TexCoord), texture(material.diffuse3, TexCoord)) ))  ) * light.color;

	// ambient
	float ambientLightStrength = 0.2;
	vec3 ambient = diffuse * ambientLightStrength * light.color;

	// specular
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	vec3 specular = (spec * vec3(texture(material.specular, TexCoord))) * light.color;

	vec3 result = ambient + diffuse + specular;
	
	FragColor = vec4(result, 1.0);
}