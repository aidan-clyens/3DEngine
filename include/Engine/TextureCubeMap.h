#pragma once

// Includes
#include "Engine/utils/types.h"
#include "Engine/Texture.h"

#include <vector>


/* TextureCubeMap
 */
class TextureCubeMap : public Texture {
    public:
        TextureCubeMap();

        void load(std::vector<unsigned char*> faces, int width, int height, int num_channels, unsigned int index);
};