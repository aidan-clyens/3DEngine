#include "Engine/Object3D.h"

#include <iostream>

/* Object3D
 */
Object3D::Object3D(Eigen::Vector3f pos, Eigen::Vector3f size):
m_position(pos),
m_size(size),
m_shader_program_id(-1)
{
    GLfloat half_size_x = m_size.x() / 2;
    GLfloat half_size_y = m_size.y() / 2;
    GLfloat half_size_z = m_size.z() / 2;

    GLfloat vertices[] = {
        m_position.x() + half_size_x, m_position.y() + half_size_y, m_position.z() + half_size_z,   // back top right
        m_position.x() - half_size_x, m_position.y() + half_size_y, m_position.z() + half_size_z,   // back top left
        m_position.x() + half_size_x, m_position.y() - half_size_y, m_position.z() + half_size_z,   // back bottom right
        m_position.x() - half_size_x, m_position.y() - half_size_y, m_position.z() + half_size_z,   // back bottom left
        m_position.x() + half_size_x, m_position.y() + half_size_y, m_position.z() - half_size_z,   // front top right
        m_position.x() - half_size_x, m_position.y() + half_size_y, m_position.z() - half_size_z,   // front top left
        m_position.x() + half_size_x, m_position.y() - half_size_y, m_position.z() - half_size_z,   // front bottom right
        m_position.x() - half_size_x, m_position.y() - half_size_y, m_position.z() - half_size_z,   // front bottom left
    };

    unsigned int indices[] = {
        // back face
        0, 1, 2,
        1, 2, 3,
        // front face
        4, 5, 6,
        5, 6, 7,
        // left face
        1, 3, 5,
        3, 5, 7,
        // right face
        0, 2, 4,
        2, 4, 6,
        // top face
        0, 1, 4,
        1, 4, 5,
        // bottom face
        2, 3, 6,
        3, 6, 7
    };

    glGenVertexArrays(1, &m_vertex_array_object);
    glGenBuffers(1, &m_vertex_buffer_object);
    glGenBuffers(1, &m_element_buffer_object);

    glBindVertexArray(m_vertex_array_object);
    glBindBuffer(GL_ARRAY_BUFFER, m_vertex_buffer_object);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_element_buffer_object);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GL_FLOAT), (void*)0);
    glEnableVertexAttribArray(0);

    // glBindBuffer(GL_ARRAY_BUFFER, 0);
    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    // glBindVertexArray(0);
}

/* Object3D
 */
Object3D::~Object3D() {
    glDeleteBuffers(1, &m_vertex_buffer_object);
    glDeleteBuffers(1, &m_element_buffer_object);
    glDeleteVertexArrays(1, &m_vertex_array_object);
}

/* render
 */
void Object3D::render() {
    // Draw vertex array
    if (m_shader_program_id >= 0) {
        glUseProgram(m_shader_program_id);
    }

    glBindVertexArray(m_vertex_array_object);
    glDrawElements(GL_TRIANGLES, OBJECT3D_CUBE_NUM_VERTICES, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    if (m_shader_program_id >= 0) {
        glUseProgram(0);
    }
}

/* attach_shader
 */
void Object3D::attach_shader(unsigned int program_id) {
    m_shader_program_id = program_id;
}
