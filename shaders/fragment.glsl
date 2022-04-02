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
    int type;       // 0 - directional, 1 - point

    vec3 vector;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    // Used to calculate attenuation for point lights
    float constant;
    float linear;
    float quadratic;
};

uniform vec3 viewPos;

uniform Material material;
uniform Light light;

uniform bool useTexture2D;
uniform bool useTextureCube;

uniform sampler2D objectTexture;
uniform samplerCube objectTextureCube;


void main()
{
    // Lighting
    vec3 lightDir = light.vector;
    float attenuation = 1.0;

    if (light.type == 0) // Directional
    {
        lightDir = normalize(-light.vector);
    }
    else if (light.type == 1) // Point
    {
        lightDir = normalize(light.vector - fs_in.FragPos);
        float distance = length(light.vector - fs_in.FragPos);
        attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
    }

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

    ambient *= attenuation;

    // diffuse
    vec3 norm = normalize(fs_in.Normal);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse =  light.diffuse * diff * material.diffuse;

    if (useTexture2D)
    {
        diffuse *= vec3(texture(objectTexture, fs_in.TexCoord));
    }
    else if (useTextureCube)
    {
        diffuse *= vec3(texture(objectTextureCube, fs_in.TexCoord3));
    }

    diffuse *= attenuation;

    // specular
    vec3 viewDir = normalize(viewPos - fs_in.FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    if (diff == 0)
    {
        spec = 0;
    }
    vec3 specular = light.specular * material.specular * spec;

    specular *= attenuation;

    vec3 color = ambient + diffuse + specular;

    FragColor = vec4(color, 1.0);
}
    