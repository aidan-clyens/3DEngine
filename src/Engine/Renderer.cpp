#include "Engine/Renderer.h"

#include "Engine/ECS/Mesh.h"
#include "Engine/Camera.h"
#include "Engine/Shader.h"


/* Renderer
 */
Renderer::Renderer(int width, int height, const std::string &path):
m_width(width),
m_height(height),
m_path(path),
m_model(mat4(1.0)),
m_view(mat4(1.0)),
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

    // Create frame buffer objectss
    glGenFramebuffers(1, &m_depth_map_buffer_object);

    // Load shaders
    m_object_shader.load(m_path + "shaders/vertex.glsl", m_path + "shaders/fragment.glsl");
    if (!m_object_shader.is_valid()) {
        std::cerr << "Object shader failed to load" << std::endl;
    }

    m_depth_shader.load(m_path + "shaders/depth_vertex.glsl", m_path + "shaders/depth_fragment.glsl");
    if (!m_depth_shader.is_valid()) {
        std::cerr << "Depth shader failed to load" << std::endl;
    }

    m_debug_depth_shader.load(m_path + "shaders/debug_depth_vertex.glsl", m_path + "shaders/debug_depth_fragment.glsl");
    if (!m_debug_depth_shader.is_valid()) {
        std::cerr << "Debug depth shader failed to load" << std::endl;
    }

    m_depth_texture.load();

    glBindFramebuffer(GL_FRAMEBUFFER, m_depth_map_buffer_object);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_depth_texture.m_texture_id, 0);
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    // Lighting
    m_light.type = LIGHT_DIRECTIONAL;
    m_light.vector = vec3(-0.2f, -1.0f, -0.3f);
    m_light.ambient = vec3(0.5, 0.5, 0.5);
    m_light.diffuse = vec3(0.5, 0.5, 0.5);
    m_light.specular = vec3(0.2, 0.2, 0.2);

    // Debug
    float quad_vertices[] = {
        // positions        // texture Coords
        -1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
        -1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
        1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
        1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
    };

    glGenVertexArrays(1, &m_debug_quad_array_object);
    glGenBuffers(1, &m_debug_quad_buffer_object);
    glBindVertexArray(m_debug_quad_array_object);
    glBindBuffer(GL_ARRAY_BUFFER, m_debug_quad_buffer_object);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quad_vertices), &quad_vertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3 * sizeof(float)));

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
void Renderer::render(std::vector<Mesh *> &meshes, Camera &camera)
{
    // Pass 1: Render to depth map
    float near_plane = 1.0f;
    float far_plane = 7.5f;

    mat4 light_projection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, near_plane, far_plane);
    mat4 light_view = glm::lookAt(m_light.vector, vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));
    mat4 light_space = light_projection * light_view;

    // Pass light space matrix to shader
    if (m_depth_shader.is_valid()) {
        m_depth_shader.enable();
        m_depth_shader.set_mat4("lightSpaceMatrix", light_space);
    }

    glViewport(0, 0, DEPTH_TEXTURE_WIDTH, DEPTH_TEXTURE_HEIGHT);
    glBindFramebuffer(GL_FRAMEBUFFER, m_depth_map_buffer_object);
    glClear(GL_DEPTH_BUFFER_BIT);

    // Render each object
    for (Mesh *mesh : meshes) {
        // Render object
        mesh->render();
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    if (m_depth_shader.is_valid()) {
        m_depth_shader.disable();
    }

    // Pass 2: Render scene as normal
    glViewport(0, 0, m_width, m_height);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Adjust view
    m_view = glm::lookAt(camera.m_position, camera.m_position + camera.m_front, camera.m_up);

    // Render each object
    for (Mesh *mesh : meshes) {
        // Select shader
        if (mesh->has_shader()) {
            if (mesh->m_shader.is_valid()) {
                mesh->m_shader.enable();
            }
        }
        else {
            if (m_object_shader.is_valid()) {
                m_object_shader.enable();

                // Pass matrices to shader
                m_object_shader.set_mat4("view", m_view);
                m_object_shader.set_mat4("projection", m_projection);

                // Pass lighting data to shader
                m_object_shader.set_vec3("material.ambient", mesh->m_material.ambient);
                m_object_shader.set_vec3("material.diffuse", mesh->m_material.diffuse);
                m_object_shader.set_vec3("material.specular", mesh->m_material.specular);
                m_object_shader.set_float("material.shininess", mesh->m_material.shininess);

                m_object_shader.set_int("light.type", (int)m_light.type);
                m_object_shader.set_vec3("light.vector", m_light.vector);
                m_object_shader.set_vec3("light.ambient", m_light.ambient);
                m_object_shader.set_vec3("light.diffuse", m_light.diffuse);
                m_object_shader.set_vec3("light.specular", m_light.specular);
                m_object_shader.set_float("light.constant", m_light.constant);
                m_object_shader.set_float("light.linear", m_light.linear);
                m_object_shader.set_float("light.quadratic", m_light.quadratic);

                m_object_shader.set_vec3("viewPos", camera.m_position);

                switch (mesh->get_material_type()) {
                    case MATERIAL_COLOR:
                        m_object_shader.set_bool("useTexture2D", false);
                        m_object_shader.set_bool("useTextureCube", false);
                        break;
                    case MATERIAL_TEXTURE_2D:
                        m_object_shader.set_bool("useTexture2D", true);
                        m_object_shader.set_bool("useTextureCube", false);
                        m_object_shader.set_int("objectTexture", 0);
                        break;
                    case MATERIAL_TEXTURE_CUBE:
                        m_object_shader.set_bool("useTexture2D", false);
                        m_object_shader.set_bool("useTextureCube", true);
                        m_object_shader.set_int("objectTextureCube", 0);
                        break;
                }
            }
        }

        // Render object
        mesh->render();

        // Deselect shader
        if (mesh->has_shader()) {
            if (mesh->m_shader.is_valid()) {
                mesh->m_shader.disable();
            }
        }
        else {
            if (m_object_shader.is_valid()) {
                m_object_shader.disable();
            }
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
}

/* set_mouse_visible
 */
void Renderer::set_mouse_visible(bool value) {
    if (value) {
        glfwSetInputMode(p_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }
    else {
        glfwSetInputMode(p_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }
}

/* add_light
 */
void Renderer::add_light(Light light) {
    m_light = light;
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