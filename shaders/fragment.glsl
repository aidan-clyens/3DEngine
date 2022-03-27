#version 330 core

in VS_OUT {
    vec3 FragPos;
    vec3 Normal;
    vec2 TexCoord;
    vec3 TexCoord3;
} fs_in;

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

uniform vec3 lightPos;
uniform vec3 viewPos;

uniform Material material;
uniform Light light;

uniform bool useTexture2D;
uniform bool useTextureCube;

uniform sampler2D objectTexture;
uniform samplerCube objectTextureCube;


void main()
{
    // ambient
    vec3 ambient = light.ambient * material.ambient;

    if (useTexture2D)
    {
        ambient *= vec3(texture(objectTexture, fs_in.TexCoord));
    }
    else if (useTextureCube)
    {
        ambient *= vec3(texture(objectTextureCube, fs_in.TexCoord3));
    }

    // diffuse
    vec3 norm = normalize(fs_in.Normal);
    float diff = max(dot(norm, lightPos), 0.0);
    vec3 diffuse =  light.diffuse * diff * material.diffuse;

    if (useTexture2D)
    {
        diffuse *= vec3(texture(objectTexture, fs_in.TexCoord));
    }
    else if (useTextureCube)
    {
        diffuse *= vec3(texture(objectTextureCube, fs_in.TexCoord3));
    }

    // specular
    vec3 viewDir = normalize(viewPos - fs_in.FragPos);
    vec3 reflectDir = reflect(-lightPos, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    if (diff == 0)
    {
        spec = 0;
    }
    vec3 specular = light.specular * material.specular * spec;

    vec3 color = ambient + diffuse + specular;

    FragColor = vec4(color, 1.0);
}
    