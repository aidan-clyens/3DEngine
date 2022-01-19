#pragma once

// Includes
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>


/* eShaderType
 */
typedef enum {
    SHADER_VERTEX,
    SHADER_FRAGMENT
} eShaderType;


/* Renderer
 */
class Renderer {
    public:
        Renderer(int width, int height);

        bool init();
        void close();

        void clear();
        void render();
        void start_update();
        void end_update();

        bool load_shader(const std::string &filename, eShaderType shader_type, unsigned int &shader_id);
        bool link_shader_program(unsigned int vertex_shader_id, unsigned int fragment_shader_id, unsigned int &program_id);

        bool is_window_closed() const;

        void set_key_callback(GLFWkeyfun callback);

    private:
        void on_key_pressed(GLFWwindow *p_window, int key, int scancode, int action, int mods);

        int m_width;
        int m_height;
        GLFWwindow *p_window;
};