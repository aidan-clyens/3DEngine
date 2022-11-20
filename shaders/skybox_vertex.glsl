#version 330 core
layout (location = 0) in vec3 aPos;

out VS_OUT {
    vec3 TexCoord3;
} vs_out;

uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position = projection * view * vec4(aPos, 1.0);
    vs_out.TexCoord3 = aPos;
}