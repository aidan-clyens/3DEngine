#pragma once

// Includes
#include "Engine/utils/types.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <string>

/* Texture
 */
class Texture {
    public:
        Texture();
        virtual ~Texture();

        void load(const std::string &texture_path, unsigned int index, unsigned int texture_type);
        void load(void *data, unsigned int index, unsigned int texture_type);

        void enable();
        void disable();

    protected:
        void free_data();

        unsigned int m_texture_id;
        unsigned int m_index;
        unsigned int m_texture_type;

        int m_texture_width;
        int m_texture_height;
        int m_num_channels;

        void *p_data;
};