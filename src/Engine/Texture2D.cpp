#include "Engine/Texture2D.h"

#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#endif
#include "stb_image.h"


/* Texture2D
 */
Texture2D::Texture2D() {

}

/* Texture2D
 */
Texture2D::Texture2D(const std::string &texture_path, unsigned int index):
m_index(index)
{
    int tex_width, tex_height, num_channels;
    unsigned char *data = stbi_load(texture_path.c_str(), &tex_width, &tex_height, &num_channels, 0);

    glGenTextures(1, &m_texture_id);

    if (data) {
        GLenum format;
        if (num_channels == 1) {
            format = GL_RED;
        }
        else if (num_channels == 3) {
            format = GL_RGB;
        }
        else if (num_channels == 4) {
            format = GL_RGBA;
        }

        glBindTexture(GL_TEXTURE_2D, m_texture_id);
        glTexImage2D(GL_TEXTURE_2D, 0, format, tex_width, tex_height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    }

    stbi_image_free(data);
}

/* enable
 */
void Texture2D::enable() {
    glActiveTexture(GL_TEXTURE0 + m_index);
    glBindTexture(GL_TEXTURE_2D, m_texture_id);
}

/* disable
 */
void Texture2D::disable() {
    glBindTexture(GL_TEXTURE_2D, 0);
}