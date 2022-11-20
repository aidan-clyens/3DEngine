#version 330 core

in VS_OUT {
    vec3 TexCoord3;
} fs_in;

out vec4 FragColor;

uniform samplerCube skyboxTexture;

void main()
{
    FragColor = texture(skyboxTexture, fs_in.TexCoord3);
}
    