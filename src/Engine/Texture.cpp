#include "Engine/Texture.h"

#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#endif
#include "stb_image.h"


/* Texture
 */
Texture::Texture():
m_index(0),
m_texture_type(GL_TEXTURE_2D)
{

}

/* Texture
 */
Texture::Texture(const std::string &texture_path, unsigned int index, unsigned int texture_type):
m_index(index),
m_texture_type(texture_type)
{
    glGenTextures(1, &m_texture_id);

    p_data = stbi_load(texture_path.c_str(), &m_texture_width, &m_texture_height, &m_num_channels, 0);
}

/* ~Texture
 */
Texture::~Texture() {
    // glDeleteTextures(1, &m_texture_id);
}

/* enable
 */
void Texture::enable() {
    glActiveTexture(GL_TEXTURE0 + m_index);
    glBindTexture(m_texture_type, m_texture_id);
}

/* disable
 */
void Texture::disable() {
    glBindTexture(m_texture_type, 0);
}

void Texture::free_data() {
    stbi_image_free(p_data);
}