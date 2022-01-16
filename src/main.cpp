// Includes
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

// Defines
#define SCREEN_WIDTH        1600
#define SCREEN_HEIGHT       900


void draw_square() {
    GLfloat vertices[] = {
        0.0, 300, 0.0,      // top left
        300, 300, 0.0,      // top right
        300, 0.0, 0.0,      // bottom right
        0.0, 0.0, 0.0       // bottom left
    };

    // Draw vertex array
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, vertices);
    glDrawArrays(GL_QUADS, 0, 4);
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
        draw_square();
        draw_point();

        // Swap buffer
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}