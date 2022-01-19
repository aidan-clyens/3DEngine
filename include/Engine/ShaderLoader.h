#pragma once

// Includes
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <string>

/* eShaderType
 */
typedef enum {
    SHADER_VERTEX,
    SHADER_FRAGMENT
} eShaderType;


/* ShaderLoader
 */
class ShaderLoader {
    public:
        bool load_shader(const std::string &filename, eShaderType shader_type, unsigned int &shader_id);
        bool link_shader_program(unsigned int vertex_shader_id, unsigned int fragment_shader_id, unsigned int &program_id);

};