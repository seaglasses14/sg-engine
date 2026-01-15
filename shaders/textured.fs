#version 330 core
in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoord;

out vec4 FragColor;

struct Material
{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
}

uniform Material material;

uniform vec3 lightColor;
uniform vec3 lightPos;
uniform sampler2D texture1;
uniform vec3 viewPos;

void main()
{
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(lightPos - FragPos);
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);

	// ambient
	vec3 ambient = material.ambient * lightColor;

	// diffuse
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = (diff * material.diffuse) * lightColor;

	// specular
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	vec3 specular = (material.specular * spec) * lightColor;

	vec3 result = (ambient + diffuse + specular) * vec3(texture(texture1, TexCoord));
	
	FragColor = vec4(result, 1.0);
}