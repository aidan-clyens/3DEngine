#include "Engine/Renderer.h"

#include "Engine/Object3D.h"
#include "Engine/Camera.h"
#include "Engine/Shader.h"


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

    glEnable(GL_CULL_FACE);

    // Use wireframe mode
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

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
void Renderer::render(std::vector<Object3D*> &objects, Camera &camera, glm::vec3 light_direction) {
    // Clear window
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Adjust view
    m_view = glm::lookAt(camera.m_position, camera.m_position + camera.m_front, camera.m_up);

    // Render each object
    for (Object3D *object : objects) {
        // Select shader
        if (object->m_shader.is_valid()) {
            object->m_shader.enable();
        }

        if (object->m_shader.is_valid()) {
            // Pass matrices to shader
            object->m_shader.set_mat4("view", m_view);
            object->m_shader.set_mat4("projection", m_projection);

            // Pass lighting data to shader
            object->m_shader.set_vec3("material.ambient", object->m_material.ambient);
            object->m_shader.set_vec3("material.diffuse", object->m_material.diffuse);
            object->m_shader.set_vec3("material.specular", object->m_material.specular);
            object->m_shader.set_float("material.shininess", object->m_material.shininess);

            object->m_shader.set_vec3("light.ambient", object->m_light.ambient);
            object->m_shader.set_vec3("light.diffuse", object->m_light.diffuse);
            object->m_shader.set_vec3("light.specular", object->m_light.specular);

            object->m_shader.set_vec3("lightDir", light_direction);
            object->m_shader.set_vec3("viewPos", camera.m_position);
            object->m_shader.set_int("objectTexture", 0);
        }

        // Render object
        object->render();

        // Deselect shader
        if (object->m_shader.is_valid()) {
            object->m_shader.disable();
        }
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