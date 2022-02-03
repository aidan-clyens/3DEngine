#pragma once

// Includes
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <vector>

#include "Engine/utils/types.h"


class Mesh;
class Camera;


/* Renderer
 */
class Renderer {
    public:
        Renderer(int width, int height);

        bool init();
        void close();

        void render(std::vector<Mesh*> &meshes, Camera &camera, vec3 light_direction);

        bool is_window_closed() const;

        void set_key_callback(GLFWkeyfun callback);
        void set_mouse_callback(GLFWcursorposfun callback);

        GLFWwindow *get_window();

    private:
        void on_key_pressed(GLFWwindow *p_window, int key, int scancode, int action, int mods);

        int m_width;
        int m_height;
        GLFWwindow *p_window;

        mat4 m_model;
        mat4 m_view;
        mat4 m_projection;
};