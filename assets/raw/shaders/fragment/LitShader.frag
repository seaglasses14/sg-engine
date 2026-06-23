#version 330 core

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoord;

out vec4 FragColor;

struct Material
{
	sampler2D diffuse;
	sampler2D specular;

	float shininess;
};

struct DirLight
{
    vec3 direction;
    vec3 color;
};

uniform Material material;
uniform DirLight dirLight;

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir);

void main()
{
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(-FragPos);

    vec3 directResult = CalcDirLight(dirLight, norm, viewDir);

    FragColor = vec4(directResult, 1.0);
}

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
    vec3 lightDir = normalize(-light.direction);

    // ambient
    float amb = 0.2;

    // diffuse
    float diff = max(dot(normal, lightDir), 0.0);

    // specular
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

    vec3 ambient = (amb * light.color) * vec3(texture(material.diffuse, TexCoord));
    vec3 diffuse = (diff * light.color) * vec3(texture(material.diffuse, TexCoord));
    //vec3 specular = (spec * light.color) * vec3(textire(material.specular, TexCoord));
    vec3 specular = (spec * light.color) * vec3(1.0, 0.65, 0.0);
    vec3 result = ambient + diffuse + specular;

    return result;
}