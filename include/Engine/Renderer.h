#pragma once

// Includes
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <vector>

#include "Engine/utils/types.h"
#include "Engine/Shader.h"
#include "Engine/DepthTexture.h"

// Forward declarations
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

        void set_mouse_visible(bool value);

        GLFWwindow *get_window();

    private:
        void on_key_pressed(GLFWwindow *p_window, int key, int scancode, int action, int mods);

        // Debug
        void render_debug_quad();

        int m_width;
        int m_height;
        GLFWwindow *p_window;

        mat4 m_model;
        mat4 m_view;
        mat4 m_projection;

        // Frame buffer objects
        unsigned int m_depth_map_buffer_object;

        // Depth map
        Shader m_depth_shader;
        Shader m_debug_depth_shader;
        DepthTexture m_depth_texture;

        // Debug
        unsigned int m_debug_quad_array_object;
        unsigned int m_debug_quad_buffer_object;
};