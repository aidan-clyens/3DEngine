#include "Engine/Renderer.h"

#include "Engine/Object3D.h"
#include "Engine/Camera.h"


/* Renderer
 */
Renderer::Renderer(int width, int height):
m_width(width),
m_height(height),
m_model(glm::mat4(1.0)),
m_view(glm::mat4(1.0)),
m_projection(glm::perspective(glm::radians((float)45.0), (float)width / (float)height, (float)0.1, (float)100.0))
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

    glViewport(0.0, 0.0, m_width, m_height);
    glfwSwapInterval(1);
    glEnable(GL_DEPTH_TEST);

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
void Renderer::render(std::vector<Object3D*> &objects, Camera &camera) {
    // Clear window
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Adjust view
    m_view = glm::lookAt(camera.m_position, camera.m_position + camera.m_front, camera.m_up);

    // Render each object
    for (Object3D *object : objects) {
        // Select shader
        glUseProgram(object->m_shader_program_id);

        // Create transformations
        m_model = glm::mat4(1.0);

        // Transform object
        m_model = glm::translate(m_model, object->m_position);
        m_model = glm::rotate(m_model, glm::radians((float)object->m_rotation.x), glm::vec3(1.0, 0.0, 0.0));
        m_model = glm::rotate(m_model, glm::radians((float)object->m_rotation.y), glm::vec3(0.0, 1.0, 0.0));
        m_model = glm::rotate(m_model, glm::radians((float)object->m_rotation.z), glm::vec3(0.0, 0.0, 1.0));

        // Get matrix uniform locations
        unsigned int model_location = glGetUniformLocation(object->m_shader_program_id, "model");
        unsigned int view_location = glGetUniformLocation(object->m_shader_program_id, "view");
        unsigned int projection_location = glGetUniformLocation(object->m_shader_program_id, "projection");

        // Pass matrices to shader
        glUniformMatrix4fv(model_location, 1, GL_FALSE, &m_model[0][0]);
        glUniformMatrix4fv(view_location, 1, GL_FALSE, &m_view[0][0]);
        glUniformMatrix4fv(projection_location, 1, GL_FALSE, &m_projection[0][0]);

        // Render object
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

/* set_mouse_callback
 */
void Renderer::set_mouse_callback(GLFWcursorposfun callback) {
    glfwSetCursorPosCallback(p_window, callback);
    glfwSetInputMode(p_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

/* is_window_closed
 */
bool Renderer::is_window_closed() const {
    return glfwWindowShouldClose(p_window);
}

/* get_window
 */
GLFWwindow *Renderer::get_window() {
    return p_window;
}