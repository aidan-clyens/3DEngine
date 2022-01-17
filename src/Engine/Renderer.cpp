#include "Engine/Renderer.h"


/* Renderer
 */
Renderer::Renderer(int width, int height):
m_width(width),
m_height(height)
{

}

/* init
 */
bool Renderer::init() {
    if (!glfwInit()) {
        std::cerr << "Failed to init GLFW" << std::endl;
        return false;
    }

    p_window = glfwCreateWindow(m_width, m_height, "Hello World", NULL, NULL);
    if (!p_window) {
        std::cerr << "Failed to create window" << std::endl;
        glfwTerminate();
        return false;
    }

    // Make the current window's context current
    glfwMakeContextCurrent(p_window);
    glfwSwapInterval(1);

    glViewport(0.0, 0.0, m_width, m_height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // x1, x2, y1, y2, z1, z2
    glOrtho(0, m_width, 0, m_height, 0, 1000);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Use wireframe mode
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    return true;
}

/* close
 */
void Renderer::close() {
    glfwDestroyWindow(p_window);
    glfwTerminate();
}

/* clear
 */
void Renderer::clear() {
    // Clear window
    glClear(GL_COLOR_BUFFER_BIT);
}

/* render
 */
void Renderer::render() {
    // Swap buffer
    glfwSwapBuffers(p_window);
    glfwPollEvents();
}

/* start_update
 */
void Renderer::start_update() {
    glPushMatrix();
}

/* end_update
 */
void Renderer::end_update() {
    glPopMatrix();
}

/* set_key_callback
 */
void Renderer::set_key_callback(GLFWkeyfun callback) {
    // Configure input
    glfwSetKeyCallback(p_window, callback);
    glfwSetInputMode(p_window, GLFW_STICKY_KEYS, 1);
}

/* is_window_closed
 */
bool Renderer::is_window_closed() const {
    return glfwWindowShouldClose(p_window);
}