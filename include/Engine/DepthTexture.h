#pragma once

// Includes
#include "Engine/utils/types.h"
#include "Engine/Texture.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <string>

// Defines
#define DEPTH_TEXTURE_WIDTH    1024
#define DEPTH_TEXTURE_HEIGHT   1024

/* DepthTexture
 */
class DepthTexture : public Texture {
    public:
        DepthTexture();

        void load();
};