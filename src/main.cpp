// Includes
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <Eigen/Core>

#include <iostream>

// Defines
#define SCREEN_WIDTH        1600
#define SCREEN_HEIGHT       900


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

void draw_point() {
    GLfloat point[] = {
        SCREEN_WIDTH / 2.0, SCREEN_HEIGHT / 2.0
    };

    // Draw vertex array
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(2, GL_FLOAT, 0, point);
    glDrawArrays(GL_POINTS, 0, 1);
    glDisableClientState(GL_VERTEX_ARRAY);
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

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    glViewport(0.0, 0.0, SCREEN_WIDTH, SCREEN_HEIGHT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, SCREEN_WIDTH, 0, SCREEN_HEIGHT, 0, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    while (!glfwWindowShouldClose(window)) {
        // Clear window
        glClear(GL_COLOR_BUFFER_BIT);

        // Render
        draw_square(Eigen::Vector3f((SCREEN_WIDTH / 2), (SCREEN_HEIGHT / 2), 0.0), 100);
        draw_point();

        // Swap buffer
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}