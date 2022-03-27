#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;
layout (location = 3) in mat4 aModel;

out VS_OUT {
    vec3 FragPos;
    vec3 Normal;
    vec2 TexCoord;
} vs_out;

uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position = projection * view * aModel * vec4(aPos, 1.0);
    vs_out.FragPos = vec3(aModel * vec4(aPos, 1.0));
    vs_out.Normal = aNormal;
    vs_out.TexCoord = aTexCoord;
}