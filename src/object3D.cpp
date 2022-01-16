#include "object3D.h"


/* Object3D
 */
Object3D::Object3D(Eigen::Vector3f pos, GLfloat width):
m_position(pos),
m_width(width)
{
    GLfloat half_width = m_width / 2;

    GLfloat vertices[] = {
        // Front face
        m_position.x() - half_width, m_position.y() - half_width, m_position.z() + half_width, // bottom left
        m_position.x() + half_width, m_position.y() - half_width, m_position.z() + half_width, // bottom right
        m_position.x() - half_width, m_position.y() + half_width, m_position.z() + half_width, // top left

        m_position.x() - half_width, m_position.y() + half_width, m_position.z() + half_width, // top left
        m_position.x() + half_width, m_position.y() - half_width, m_position.z() + half_width, // bottom right
        m_position.x() + half_width, m_position.y() + half_width, m_position.z() + half_width, // top right

        // Back face
        m_position.x() - half_width, m_position.y() - half_width, m_position.z() - half_width, // bottom left
        m_position.x() + half_width, m_position.y() - half_width, m_position.z() - half_width, // bottom right
        m_position.x() - half_width, m_position.y() + half_width, m_position.z() - half_width, // top left

        m_position.x() - half_width, m_position.y() + half_width, m_position.z() - half_width, // top left
        m_position.x() + half_width, m_position.y() - half_width, m_position.z() - half_width, // bottom right
        m_position.x() + half_width, m_position.y() + half_width, m_position.z() - half_width, // top right

        // Left face
        m_position.x() - half_width, m_position.y() - half_width, m_position.z() + half_width, // bottom left
        m_position.x() - half_width, m_position.y() - half_width, m_position.z() - half_width, // bottom right
        m_position.x() - half_width, m_position.y() + half_width, m_position.z() + half_width, // top left

        m_position.x() - half_width, m_position.y() + half_width, m_position.z() + half_width, // top left
        m_position.x() - half_width, m_position.y() - half_width, m_position.z() - half_width, // bottom right
        m_position.x() - half_width, m_position.y() + half_width, m_position.z() - half_width, // top right

        // Right face
        m_position.x() + half_width, m_position.y() - half_width, m_position.z() + half_width, // bottom left
        m_position.x() + half_width, m_position.y() - half_width, m_position.z() - half_width, // bottom right
        m_position.x() + half_width, m_position.y() + half_width, m_position.z() + half_width, // top left

        m_position.x() + half_width, m_position.y() + half_width, m_position.z() + half_width, // top left
        m_position.x() + half_width, m_position.y() - half_width, m_position.z() - half_width, // bottom right
        m_position.x() + half_width, m_position.y() + half_width, m_position.z() - half_width, // top right

        // Top face
        m_position.x() + half_width, m_position.y() + half_width, m_position.z() + half_width, // bottom left
        m_position.x() + half_width, m_position.y() + half_width, m_position.z() - half_width, // bottom right
        m_position.x() - half_width, m_position.y() + half_width, m_position.z() + half_width, // top left

        m_position.x() - half_width, m_position.y() + half_width, m_position.z() + half_width, // top left
        m_position.x() + half_width, m_position.y() + half_width, m_position.z() - half_width, // bottom right
        m_position.x() - half_width, m_position.y() + half_width, m_position.z() - half_width, // top right

        // Bottom face
        m_position.x() + half_width, m_position.y() - half_width, m_position.z() + half_width, // bottom left
        m_position.x() + half_width, m_position.y() - half_width, m_position.z() - half_width, // bottom right
        m_position.x() - half_width, m_position.y() - half_width, m_position.z() + half_width, // top left

        m_position.x() - half_width, m_position.y() - half_width, m_position.z() + half_width, // top left
        m_position.x() + half_width, m_position.y() - half_width, m_position.z() - half_width, // bottom right
        m_position.x() - half_width, m_position.y() - half_width, m_position.z() - half_width  // top right
    };

    std::copy(std::begin(vertices), std::end(vertices), std::begin(m_vertices));
}

/* render
 */
void Object3D::render() {
    // Draw vertex array
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, m_vertices);
    glDrawArrays(GL_TRIANGLES, 0, OBJECT3D_CUBE_NUM_FACES);
    glDisableClientState(GL_VERTEX_ARRAY);
}