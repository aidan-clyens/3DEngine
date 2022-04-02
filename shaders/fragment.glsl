#version 330 core

#define MAX_LIGHTS  16


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
uniform Light directionalLight;
uniform Light pointLights[MAX_LIGHTS];
uniform int numberPointLights;

uniform bool useTexture2D;
uniform bool useTextureCube;

uniform sampler2D objectTexture;
uniform samplerCube objectTextureCube;


vec3 CalculateLighting(Light light, vec3 lightDir, float attenuation)
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

    return ambient + diffuse + specular;
}

vec3 CalculateDirectionalLight(Light light)
{
    return CalculateLighting(light, normalize(-light.vector), 1.0);
}

vec3 CalculatePointLight(Light light)
{
    vec3 lightDir = normalize(light.vector - fs_in.FragPos);
    float distance = length(light.vector - fs_in.FragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

    return CalculateLighting(light, lightDir, attenuation);
}

void main()
{
    vec3 color = CalculateDirectionalLight(directionalLight);

    for (int i = 0; i < numberPointLights; i++)
    {
        color += CalculatePointLight(pointLights[i]);
    }

    FragColor = vec4(color, 1.0);
}
    