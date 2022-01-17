// Includes
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <Eigen/Core>

#include <iostream>
#include <vector>

#include "renderer.h"
#include "object3D.h"


// Defines
#define SCREEN_WIDTH        1600
#define SCREEN_HEIGHT       900

// Global variables
Eigen::Vector3f rotation_speed = Eigen::Vector3f(0, 0, 0);


void on_key_pressed(GLFWwindow *p_window, int key, int scancode, int action, int mods) {
    std::cout << "Key: " << key << std::endl;

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

    if (!renderer.init()) {
        std::cerr << "Failed to init Renderer" << std::endl;
        renderer.close();
        return -1;
    }

    renderer.set_key_callback(on_key_pressed);

    Eigen::Vector3f position = Eigen::Vector3f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, -500);
    GLfloat width = 250;

    std::vector<Object3D> objects; 

    Object3D cube(position, width);
    objects.push_back(cube);

    // Main rendering loop
    while (!renderer.is_window_closed()) {
        renderer.clear();

        // Render objects
        for (Object3D object : objects) {
            object.render();
        }

        renderer.render();
    }

    renderer.close();

    return 0;
}
