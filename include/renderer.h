#pragma once

// Includes
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>


/* Renderer
 */
class Renderer {
    public:
        Renderer(int width, int height);

        bool init();
        void close();

        void clear();
        void render();

        bool is_window_closed() const;

        void set_key_callback(GLFWkeyfun callback);

    private:
        void on_key_pressed(GLFWwindow *p_window, int key, int scancode, int action, int mods);

        int m_width;
        int m_height;
        GLFWwindow *p_window;
};