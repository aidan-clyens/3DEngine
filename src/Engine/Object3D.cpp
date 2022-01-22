#include "Engine/Object3D.h"


/* Object3D
 */
Object3D::Object3D(glm::vec3 pos, glm::vec3 rotation, glm::vec3 size):
m_position(pos),
m_rotation(rotation),
m_size(size)
{
    GLfloat half_size_x = m_size.x / 2;
    GLfloat half_size_y = m_size.y / 2;
    GLfloat half_size_z = m_size.z / 2;

    float vertices[] = {
        -half_size_x, -half_size_x, -half_size_x,  0.0f,  0.0f, -1.0f,
        half_size_x, -half_size_x, -half_size_x,  0.0f,  0.0f, -1.0f, 
        half_size_x,  half_size_x, -half_size_x,  0.0f,  0.0f, -1.0f,
        half_size_x,  half_size_x, -half_size_x,  0.0f,  0.0f, -1.0f, 
        -half_size_x,  half_size_x, -half_size_x,  0.0f,  0.0f, -1.0f, 
        -half_size_x, -half_size_x, -half_size_x,  0.0f,  0.0f, -1.0f, 

        -half_size_x, -half_size_x,  half_size_x,  0.0f,  0.0f, 1.0f,
        half_size_x, -half_size_x,  half_size_x,  0.0f,  0.0f, 1.0f,
        half_size_x,  half_size_x,  half_size_x,  0.0f,  0.0f, 1.0f,
        half_size_x,  half_size_x,  half_size_x,  0.0f,  0.0f, 1.0f,
        -half_size_x,  half_size_x,  half_size_x,  0.0f,  0.0f, 1.0f,
        -half_size_x, -half_size_x,  half_size_x,  0.0f,  0.0f, 1.0f,

        -half_size_x,  half_size_x,  half_size_x, -1.0f,  0.0f,  0.0f,
        -half_size_x,  half_size_x, -half_size_x, -1.0f,  0.0f,  0.0f,
        -half_size_x, -half_size_x, -half_size_x, -1.0f,  0.0f,  0.0f,
        -half_size_x, -half_size_x, -half_size_x, -1.0f,  0.0f,  0.0f,
        -half_size_x, -half_size_x,  half_size_x, -1.0f,  0.0f,  0.0f,
        -half_size_x,  half_size_x,  half_size_x, -1.0f,  0.0f,  0.0f,

        half_size_x,  half_size_x,  half_size_x,  1.0f,  0.0f,  0.0f,
        half_size_x,  half_size_x, -half_size_x,  1.0f,  0.0f,  0.0f,
        half_size_x, -half_size_x, -half_size_x,  1.0f,  0.0f,  0.0f,
        half_size_x, -half_size_x, -half_size_x,  1.0f,  0.0f,  0.0f,
        half_size_x, -half_size_x,  half_size_x,  1.0f,  0.0f,  0.0f,
        half_size_x,  half_size_x,  half_size_x,  1.0f,  0.0f,  0.0f,

        -half_size_x, -half_size_x, -half_size_x,  0.0f, -1.0f,  0.0f,
        half_size_x, -half_size_x, -half_size_x,  0.0f, -1.0f,  0.0f,
        half_size_x, -half_size_x,  half_size_x,  0.0f, -1.0f,  0.0f,
        half_size_x, -half_size_x,  half_size_x,  0.0f, -1.0f,  0.0f,
        -half_size_x, -half_size_x,  half_size_x,  0.0f, -1.0f,  0.0f,
        -half_size_x, -half_size_x, -half_size_x,  0.0f, -1.0f,  0.0f,

        -half_size_x,  half_size_x, -half_size_x,  0.0f,  1.0f,  0.0f,
        half_size_x,  half_size_x, -half_size_x,  0.0f,  1.0f,  0.0f,
        half_size_x,  half_size_x,  half_size_x,  0.0f,  1.0f,  0.0f,
        half_size_x,  half_size_x,  half_size_x,  0.0f,  1.0f,  0.0f,
        -half_size_x,  half_size_x,  half_size_x,  0.0f,  1.0f,  0.0f,
        -half_size_x,  half_size_x, -half_size_x,  0.0f,  1.0f,  0.0f
    };

    // Create VBO and VAO
    glGenVertexArrays(1, &m_vertex_array_object);
    glGenBuffers(1, &m_vertex_buffer_object);

    glBindVertexArray(m_vertex_array_object);
    glBindBuffer(GL_ARRAY_BUFFER, m_vertex_buffer_object);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Initialize lighting data
    m_lighting_data.color = glm::vec3(1, 1, 1);
    m_lighting_data.light_color = glm::vec3(1, 1, 1);
    m_lighting_data.ambient_strength = 1;
}

/* Object3D
 */
Object3D::~Object3D() {
    glDeleteBuffers(1, &m_vertex_buffer_object);
    glDeleteVertexArrays(1, &m_vertex_array_object);
}

/* get_position
 */
glm::vec3 Object3D::get_position() const {
    return m_position;
}

/* get_rotation
 */
glm::vec3 Object3D::get_rotation() const {
    return m_rotation;
}

/* get_size
 */
glm::vec3 Object3D::get_size() const {
    return m_size;
}

/* set_position
 */
void Object3D::set_position(glm::vec3 position) {
    m_position = position;
}

/* set_rotation
 */
void Object3D::set_rotation(glm::vec3 rotation) {
    m_rotation = rotation;
}

/* attach_shader
 */
void Object3D::attach_shader(Shader shader) {
    m_shader = shader;
}

/* set_color
 */
void Object3D::set_lighting_data(LightingData data) {
    m_lighting_data.color = data.color;
    m_lighting_data.light_color = data.light_color;
    m_lighting_data.ambient_strength = data.ambient_strength;
}

/* set_color
 */
void Object3D::set_color(glm::vec3 color) {
    m_lighting_data.color = color;
}

/* set_light_color
 */
void Object3D::set_light_color(glm::vec3 color) {
    m_lighting_data.light_color = color;
}
