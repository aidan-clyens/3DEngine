#pragma once

// Includes
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <string>


/* Texture2D
 */
class Texture2D {
    public:
        Texture2D();
        Texture2D(const std::string &texture_path, unsigned int index);

        void enable();
        void disable();

    private:
        unsigned int m_texture_id;
        unsigned int m_index;
};