#pragma once

// Includes
#include "Engine/Texture.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <string>


/* Texture2D
 */
class Texture2D : public Texture {
    public:
        Texture2D();
        Texture2D(const std::string &texture_path, unsigned int index);
};