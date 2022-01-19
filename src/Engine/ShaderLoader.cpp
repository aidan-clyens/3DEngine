#include "Engine/ShaderLoader.h"


/* load_shader
 */
bool ShaderLoader::load_shader(const std::string &filename, eShaderType shader_type, unsigned int &shader_id) {
    std::ifstream file;
    std::string content;
    int success;
    char info_log[512];

    // Read content from GLSL file
    file.open(filename);
    if (file.is_open()) {
        std::string line = "";
        while (!file.eof()) {
            std::getline(file, line);
            content.append(line + "\n");
        }
    }
    else {
        std::cerr <<  "Failed to open file " << filename << std::endl;
        return false;
    }
    file.close();

    const char *buffer = content.c_str();

    // Compile shader
    if (shader_type == SHADER_VERTEX) {
        shader_id = glCreateShader(GL_VERTEX_SHADER);
    }
    else if (shader_type == SHADER_FRAGMENT) {
        shader_id = glCreateShader(GL_FRAGMENT_SHADER);
    }

    glShaderSource(shader_id, 1, &buffer, NULL);
    glCompileShader(shader_id);

    // Get shader compilation status
    glGetShaderiv(shader_id, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader_id, 512, NULL, info_log);
        if (shader_type == SHADER_VERTEX) {
            std::cerr << "ERROR: Vertex Shader compilation FAILED\n" << info_log << std::endl;
        }
        else if (shader_type == SHADER_FRAGMENT) {
            std::cerr << "ERROR: Fragment Shader compilation FAILED\n" << info_log << std::endl;
        }
        return false;
    }

    return true;
}

/* link_shader_program
 */
bool ShaderLoader::link_shader_program(unsigned int vertex_shader_id, unsigned int fragment_shader_id, unsigned int &program_id) {
    int success;
    char info_log[512];

    program_id = glCreateProgram();

    // Link shader program
    glAttachShader(program_id, vertex_shader_id);
    glAttachShader(program_id, fragment_shader_id);
    glLinkProgram(program_id);

    glDeleteShader(vertex_shader_id);
    glDeleteShader(fragment_shader_id);

    // Get shader program link status
    glGetProgramiv(program_id, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(program_id, 512, NULL, info_log);
        std::cerr << "ERROR: Shader linking FAILED\n" << info_log << std::endl;
        return false;
    }

    return true;
}
