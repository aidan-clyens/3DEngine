#pragma once

#include <string>


unsigned char *load_image_data(const std::string &path, int *width, int *height, int *num_channels);

void free_image_data(unsigned char *data);