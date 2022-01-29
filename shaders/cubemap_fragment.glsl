#version 330 core

in vec3 FragPos;
in vec3 Normal;
in vec3 TexCoord3;
out vec4 FragColor;

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

struct Light {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform vec3 lightDir;
uniform vec3 viewPos;

uniform Material material;
uniform Light light;

uniform samplerCube objectTexture;

void main()
{
    // ambient
    vec3 ambient = light.ambient * material.ambient * vec3(texture(objectTexture, TexCoord3));

    // diffuse
    vec3 norm = normalize(Normal);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * material.diffuse * vec3(texture(objectTexture, TexCoord3));

    // specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * material.specular * spec;

    vec3 color = ambient + diffuse + specular;

    FragColor = vec4(color, 1.0);
}
