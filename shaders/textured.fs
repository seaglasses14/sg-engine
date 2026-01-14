#version 330 core
in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoord;

out vec4 FragColor;

uniform vec3 lightColor;
uniform vec3 lightPos;
uniform sampler2D texture1;
uniform vec3 viewPos;

void main()
{
	float ambientStrength = 0.1;
	float specularStrength = 0.5;
	vec3 ambientLight = ambientStrength * lightColor;

	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(lightPos - FragPos);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * lightColor;
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
	vec3 specular = specularStrength * spec * lightColor;

	vec3 result = (ambientLight + diffuse) * vec3(texture(texture1, TexCoord));
	
	FragColor = vec4(result, 1.0);
}