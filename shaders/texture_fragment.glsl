#version 330 core

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoord;
out vec4 FragColor;

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

uniform vec3 lightPos;
uniform vec3 viewPos;

uniform Material material;

uniform sampler2D objectTexture;

void main()
{
    // ambient
    vec3 ambient = material.ambient * vec3(texture(objectTexture, TexCoord));

    // diffuse
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * material.diffuse * vec3(texture(objectTexture, TexCoord));

    // specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = material.specular * spec;

    vec3 color = ambient + diffuse + specular;

    FragColor = vec4(color, 1.0);
}
    