#include "Engine/Texture.h"
#include "Engine/utils/load_image.h"


/* Texture
 */
Texture::Texture():
m_index(0),
m_texture_type(GL_TEXTURE_2D)
{

}

/* load
 */
void Texture::load(const std::string &texture_path, unsigned int index, unsigned int texture_type) {
    m_index = index;
    m_texture_type = texture_type;

    glGenTextures(1, &m_texture_id);

    p_data = load_image_data(texture_path, &m_texture_width, &m_texture_height, &m_num_channels);
}

/* load
 */
void Texture::load(unsigned char *data, unsigned int index, unsigned int texture_type) {
    m_index = index;
    m_texture_type = texture_type;

    glGenTextures(1, &m_texture_id);

    p_data = data;
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
    free_image_data(p_data);
}