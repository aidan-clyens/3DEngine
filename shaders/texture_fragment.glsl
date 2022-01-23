#version 330 core

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoord;
out vec4 FragColor;

uniform vec3 objectColor;
uniform vec3 lightColor;
uniform float ambientStrength;
uniform float specularStrength;
uniform float shininess;
uniform vec3 lightPos;
uniform vec3 viewPos;

uniform sampler2D objectTexture;

void main()
{
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);

    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);

    vec3 ambient = ambientStrength * vec3(texture(objectTexture, TexCoord)) * lightColor;
    vec3 diffuse = diff * vec3(texture(objectTexture, TexCoord)) * lightColor;
    vec3 specular = specularStrength * spec * lightColor;
    vec3 color = (ambient + diffuse + specular) * objectColor;

    FragColor = vec4(color, 1.0);
}
    