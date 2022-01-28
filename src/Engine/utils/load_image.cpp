#include "Engine/utils/load_image.h"

#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#endif
#include "stb_image.h"


unsigned char *load_image_data(const std::string &path, int *width, int *height, int *num_channels) {
    return stbi_load(path.c_str(), width, height, num_channels, 0);
}

void free_image_data(unsigned char *data) {
    stbi_image_free(data);
}