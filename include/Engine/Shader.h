#pragma once

// Includes
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <string>

/* eShaderType
 */
typedef enum
{
    SHADER_VERTEX,
    SHADER_FRAGMENT
} eShaderType;

/* eShaderType
 */
class Shader {
    public:
        Shader();
        Shader(const std::string &vertex_shader_path, const std::string &fragment_shader_path);

        void enable();
        void disable();

        bool is_valid() const;

        unsigned int get_program_id() const;

    private:
        bool load_shader(const std::string &filename, eShaderType shader_type, unsigned int &shader_id);
        bool link_shader_program(unsigned int vertex_shader_id, unsigned int fragment_shader_id);

        std::string m_vertex_shader_path;
        std::string m_fragment_shader_path;

        unsigned int m_program_id;
        bool m_is_valid;
};