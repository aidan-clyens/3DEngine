// Includes
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

// Defines
#define SCREEN_WIDTH        1600
#define SCREEN_HEIGHT       900


float vertices[] = {
    0.0, 0.5, 0.0,       // Vertex 1
    0.5, -0.5, 0.0,      // Vertex 2
    -0.5, -0.5, 0.0      // Vertex 3
};


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

    while (!glfwWindowShouldClose(window)) {
        // Clear window
        glClear(GL_COLOR_BUFFER_BIT);

        // Draw vertex array
        glEnableClientState(GL_VERTEX_ARRAY);
        glVertexPointer(3, GL_FLOAT, 0, vertices);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glDisableClientState(GL_VERTEX_ARRAY);

        // Swap buffer
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}