// Includes
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <Eigen/Core>

#include <iostream>
#include <vector>

#include "Engine/Renderer.h"
#include "Engine/Object3D.h"
#include "Engine/ShaderLoader.h"


// Defines
#define SCREEN_WIDTH        1600
#define SCREEN_HEIGHT       900

// Global variables
Eigen::Vector3f rotation_speed = Eigen::Vector3f(0, 0, 0);

// Class definitions
/* Cube
 */
class Cube : public Object3D {
    public:
        Cube(Eigen::Vector3f pos, float width):
        Object3D(pos, Eigen::Vector3f(width, width, width))
        {

        }
};


void on_key_pressed(GLFWwindow *p_window, int key, int scancode, int action, int mods) {
    GLfloat speed = 5;

    if (action == GLFW_PRESS || action == GLFW_REPEAT) {
        switch (key) {
            // Up
            case GLFW_KEY_W:
                rotation_speed[1] += speed;
                break;

            // Down
            case GLFW_KEY_S:
                rotation_speed[1] -= speed;
                break;

            // Left
            case GLFW_KEY_A:
                rotation_speed[0] -= speed;
                break;

            // Right
            case GLFW_KEY_D:
                rotation_speed[0] += speed;
                break;

            default:
                break;
        }
    }
}

int main(int argc, char **argv) {
    Renderer renderer(SCREEN_WIDTH, SCREEN_HEIGHT);
    ShaderLoader shader_loader;

    if (!renderer.init()) {
        std::cerr << "Failed to init Renderer" << std::endl;
        renderer.close();
        return -1;
    }

    renderer.set_key_callback(on_key_pressed);

    // Load shaders
    unsigned int vertex_shader_id;
    unsigned int fragment_shader_id;
    unsigned int shader_program_id;
    if (shader_loader.load_shader("shaders/vertex.glsl", SHADER_VERTEX, vertex_shader_id) &&
        shader_loader.load_shader("shaders/fragment.glsl", SHADER_FRAGMENT, fragment_shader_id)) {

        shader_loader.link_shader_program(vertex_shader_id, fragment_shader_id, shader_program_id);
    }

    // Create objects
    Eigen::Vector3f position = Eigen::Vector3f(0, 0, 0);
    float width = 1;

    std::vector<Object3D*> objects;

    Cube *cube = new Cube(position, width);
    cube->attach_shader(shader_program_id);
    objects.push_back(cube);

    // Main rendering loop
    while (!renderer.is_window_closed()) {
        renderer.render(objects);
    }

    for (Object3D *object : objects) {
        delete object;
    }

    renderer.close();

    return 0;
}
