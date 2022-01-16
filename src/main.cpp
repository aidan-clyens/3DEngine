// Includes
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <Eigen/Core>

#include <iostream>

// Defines
#define SCREEN_WIDTH        1600
#define SCREEN_HEIGHT       900

// Global variables
Eigen::Vector3f translation_speed = Eigen::Vector3f(0, 0, 0);


void draw_cube(Eigen::Vector3f center_pos, GLfloat width) {
    GLfloat half_width = width / 2;

    GLfloat vertices[] = {
        // Front face
        center_pos.x() - half_width, center_pos.y() - half_width, center_pos.z() + half_width,      // bottom left
        center_pos.x() + half_width, center_pos.y() - half_width, center_pos.z() + half_width,      // bottom right
        center_pos.x() - half_width, center_pos.y() + half_width, center_pos.z() + half_width,      // top left

        center_pos.x() - half_width, center_pos.y() + half_width, center_pos.z() + half_width,      // top left
        center_pos.x() + half_width, center_pos.y() - half_width, center_pos.z() + half_width,      // bottom right
        center_pos.x() + half_width, center_pos.y() + half_width, center_pos.z() + half_width,      // top right

        // Back face
        center_pos.x() - half_width, center_pos.y() - half_width, center_pos.z() - half_width,      // bottom left
        center_pos.x() + half_width, center_pos.y() - half_width, center_pos.z() - half_width,      // bottom right
        center_pos.x() - half_width, center_pos.y() + half_width, center_pos.z() - half_width,      // top left

        center_pos.x() - half_width, center_pos.y() + half_width, center_pos.z() - half_width,      // top left
        center_pos.x() + half_width, center_pos.y() - half_width, center_pos.z() - half_width,      // bottom right
        center_pos.x() + half_width, center_pos.y() + half_width, center_pos.z() - half_width,      // top right

        // Left face
        center_pos.x() - half_width, center_pos.y() - half_width, center_pos.z() + half_width,      // bottom left
        center_pos.x() - half_width, center_pos.y() - half_width, center_pos.z() - half_width,      // bottom right
        center_pos.x() - half_width, center_pos.y() + half_width, center_pos.z() + half_width,      // top left

        center_pos.x() - half_width, center_pos.y() + half_width, center_pos.z() + half_width,      // top left
        center_pos.x() - half_width, center_pos.y() - half_width, center_pos.z() - half_width,      // bottom right
        center_pos.x() - half_width, center_pos.y() + half_width, center_pos.z() - half_width,      // top right

        // Right face
        center_pos.x() + half_width, center_pos.y() - half_width, center_pos.z() + half_width,      // bottom left
        center_pos.x() + half_width, center_pos.y() - half_width, center_pos.z() - half_width,      // bottom right
        center_pos.x() + half_width, center_pos.y() + half_width, center_pos.z() + half_width,      // top left

        center_pos.x() + half_width, center_pos.y() + half_width, center_pos.z() + half_width,      // top left
        center_pos.x() + half_width, center_pos.y() - half_width, center_pos.z() - half_width,      // bottom right
        center_pos.x() + half_width, center_pos.y() + half_width, center_pos.z() - half_width,      // top right

        // Top face
        center_pos.x() + half_width, center_pos.y() + half_width, center_pos.z() + half_width,      // bottom left
        center_pos.x() + half_width, center_pos.y() + half_width, center_pos.z() - half_width,      // bottom right
        center_pos.x() - half_width, center_pos.y() + half_width, center_pos.z() + half_width,      // top left

        center_pos.x() - half_width, center_pos.y() + half_width, center_pos.z() + half_width,      // top left
        center_pos.x() + half_width, center_pos.y() + half_width, center_pos.z() - half_width,      // bottom right
        center_pos.x() - half_width, center_pos.y() + half_width, center_pos.z() - half_width,      // top right

        // Bottom face
        center_pos.x() + half_width, center_pos.y() - half_width, center_pos.z() + half_width,      // bottom left
        center_pos.x() + half_width, center_pos.y() - half_width, center_pos.z() - half_width,      // bottom right
        center_pos.x() - half_width, center_pos.y() - half_width, center_pos.z() + half_width,      // top left

        center_pos.x() - half_width, center_pos.y() - half_width, center_pos.z() + half_width,      // top left
        center_pos.x() + half_width, center_pos.y() - half_width, center_pos.z() - half_width,      // bottom right
        center_pos.x() - half_width, center_pos.y() - half_width, center_pos.z() - half_width      // top right
    };

    // Draw vertex array
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, vertices);
    glDrawArrays(GL_TRIANGLES, 0, 6 * 6);
    glDisableClientState(GL_VERTEX_ARRAY);
}

void draw_square(Eigen::Vector3f center_pos, GLfloat width) {
    GLfloat vertices[] = {
        // x, y, z
        center_pos.x() - width / 2, center_pos.y() - width / 2, center_pos.z(),      // bottom left
        center_pos.x() + width / 2, center_pos.y() - width / 2, center_pos.z(),      // bottom right
        center_pos.x() - width / 2, center_pos.y() + width / 2, center_pos.z(),      // top left

        center_pos.x() - width / 2, center_pos.y() + width / 2, center_pos.z(),      // top left
        center_pos.x() + width / 2, center_pos.y() - width / 2, center_pos.z(),      // bottom right
        center_pos.x() + width / 2, center_pos.y() + width / 2, center_pos.z()       // top right
    };

    // Draw vertex array
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, vertices);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glDisableClientState(GL_VERTEX_ARRAY);
}

void draw_point(Eigen::Vector3f pos) {
    GLfloat point[] = {
        pos.x(), pos.y(), pos.z()
    };

    // Draw vertex array
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, point);
    glDrawArrays(GL_POINTS, 0, 1);
    glDisableClientState(GL_VERTEX_ARRAY);
}

void on_key_pressed(GLFWwindow *p_window, int key, int scancode, int action, int mods) {
    std::cout << "Key: " << key << std::endl;

    GLfloat speed = 5;

    switch (key) {
        // Up
        case GLFW_KEY_W:
            if (action == GLFW_PRESS || action == GLFW_REPEAT) {
                translation_speed[1] += speed;
            }
            break;

        // Down
        case GLFW_KEY_S:
            if (action == GLFW_PRESS || action == GLFW_REPEAT) {
                translation_speed[1] -= speed;
            }
            break;

        // Left
        case GLFW_KEY_A:
            if (action == GLFW_PRESS || action == GLFW_REPEAT) {
                translation_speed[0] -= speed;
            }
            break;

        // Right
        case GLFW_KEY_D:
            if (action == GLFW_PRESS || action == GLFW_REPEAT) {
                translation_speed[0] += speed;
            }
            break;

        default:
            break;
    }
}

int main(int argc, char **argv) {
    if (!glfwInit()) {
        std::cerr << "Failed to init GLFW" << std::endl;        
    }

    GLFWwindow *window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Hello World", NULL, NULL);
    if (!window) {
        std::cerr << "Failed to create window" << std::endl;
        glfwTerminate();
        return -1;
    }

    // Configure input
    glfwSetKeyCallback(window, on_key_pressed);
    glfwSetInputMode(window, GLFW_STICKY_KEYS, 1);

    // Make the current window's context current
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    glViewport(0.0, 0.0, SCREEN_WIDTH, SCREEN_HEIGHT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // x1, x2, y1, y2, z1, z2
    glOrtho(0, SCREEN_WIDTH, 0, SCREEN_HEIGHT, 0, 1000);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    Eigen::Vector3f position = Eigen::Vector3f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0);
    GLfloat width = 250;

    // Main rendering loop
    while (!glfwWindowShouldClose(window)) {
        // Clear window
        glClear(GL_COLOR_BUFFER_BIT);

        // Transform
        glPushMatrix();
        glTranslatef(translation_speed.x(), translation_speed.y(), translation_speed.z());

        // Render
        draw_cube(position, width);

        glPopMatrix();

        // Swap buffer
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}