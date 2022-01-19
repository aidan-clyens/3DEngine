#include "Engine/Renderer.h"

#include "Engine/Object3D.h"


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

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    p_window = glfwCreateWindow(m_width, m_height, "Hello World", NULL, NULL);
    if (!p_window) {
        std::cerr << "Failed to create window" << std::endl;
        glfwTerminate();
        return false;
    }

    // Make the current window's context current
    glfwMakeContextCurrent(p_window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to init GLAD" << std::endl;
        glfwTerminate();
        return false;
    }

    std::cout << "OpenGL Version: "     << glGetString(GL_VERSION)                  << std::endl;
    std::cout << "GLSL Version: "       << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
    std::cout << "OpenGL Vendor: "      << glGetString(GL_VENDOR)                   << std::endl;
    std::cout << "OpenGL Renderer: "    << glGetString(GL_RENDERER)                 << std::endl;

    glfwSwapInterval(1);

    glViewport(0.0, 0.0, m_width, m_height);

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

/* render
 */
void Renderer::render(std::vector<Object3D*> &objects) {
    // Clear window
    glClear(GL_COLOR_BUFFER_BIT);

    // Render each object
    for (Object3D *object : objects) {
        // Select shader
        glUseProgram(object->m_shader_program_id);

        glBindVertexArray(object->m_vertex_array_object);
        glDrawElements(GL_TRIANGLES, OBJECT3D_CUBE_NUM_VERTICES, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        // Deselect shader
        glUseProgram(0);
    }

    // Swap buffer
    glfwSwapBuffers(p_window);
    glfwPollEvents();
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