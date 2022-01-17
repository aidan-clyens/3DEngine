#include "Engine/Object3D.h"


/* Object3D
 */
Object3D::Object3D(Eigen::Vector3f pos, Eigen::Vector3f size):
m_position(pos),
m_size(size)
{
    GLfloat half_size_x = m_size.x() / 2;
    GLfloat half_size_y = m_size.y() / 2;
    GLfloat half_size_z = m_size.z() / 2;

    GLfloat vertices[] = {
        // Front face
        m_position.x() - half_size_x, m_position.y() - half_size_y, m_position.z() + half_size_z, // bottom left
        m_position.x() + half_size_x, m_position.y() - half_size_y, m_position.z() + half_size_z, // bottom right
        m_position.x() - half_size_x, m_position.y() + half_size_y, m_position.z() + half_size_z, // top left

        m_position.x() - half_size_x, m_position.y() + half_size_y, m_position.z() + half_size_z, // top left
        m_position.x() + half_size_x, m_position.y() - half_size_y, m_position.z() + half_size_z, // bottom right
        m_position.x() + half_size_x, m_position.y() + half_size_y, m_position.z() + half_size_z, // top right

        // Back face
        m_position.x() - half_size_x, m_position.y() - half_size_y, m_position.z() - half_size_z, // bottom left
        m_position.x() + half_size_x, m_position.y() - half_size_y, m_position.z() - half_size_z, // bottom right
        m_position.x() - half_size_x, m_position.y() + half_size_y, m_position.z() - half_size_z, // top left

        m_position.x() - half_size_x, m_position.y() + half_size_y, m_position.z() - half_size_z, // top left
        m_position.x() + half_size_x, m_position.y() - half_size_y, m_position.z() - half_size_z, // bottom right
        m_position.x() + half_size_x, m_position.y() + half_size_y, m_position.z() - half_size_z, // top right

        // Left face
        m_position.x() - half_size_x, m_position.y() - half_size_y, m_position.z() + half_size_z, // bottom left
        m_position.x() - half_size_x, m_position.y() - half_size_y, m_position.z() - half_size_z, // bottom right
        m_position.x() - half_size_x, m_position.y() + half_size_y, m_position.z() + half_size_z, // top left

        m_position.x() - half_size_x, m_position.y() + half_size_y, m_position.z() + half_size_z, // top left
        m_position.x() - half_size_x, m_position.y() - half_size_y, m_position.z() - half_size_z, // bottom right
        m_position.x() - half_size_x, m_position.y() + half_size_y, m_position.z() - half_size_z, // top right

        // Right face
        m_position.x() + half_size_x, m_position.y() - half_size_y, m_position.z() + half_size_z, // bottom left
        m_position.x() + half_size_x, m_position.y() - half_size_y, m_position.z() - half_size_z, // bottom right
        m_position.x() + half_size_x, m_position.y() + half_size_y, m_position.z() + half_size_z, // top left

        m_position.x() + half_size_x, m_position.y() + half_size_y, m_position.z() + half_size_z, // top left
        m_position.x() + half_size_x, m_position.y() - half_size_y, m_position.z() - half_size_z, // bottom right
        m_position.x() + half_size_x, m_position.y() + half_size_y, m_position.z() - half_size_z, // top right

        // Top face
        m_position.x() + half_size_x, m_position.y() + half_size_y, m_position.z() + half_size_z, // bottom left
        m_position.x() + half_size_x, m_position.y() + half_size_y, m_position.z() - half_size_z, // bottom right
        m_position.x() - half_size_x, m_position.y() + half_size_y, m_position.z() + half_size_z, // top left

        m_position.x() - half_size_x, m_position.y() + half_size_y, m_position.z() + half_size_z, // top left
        m_position.x() + half_size_x, m_position.y() + half_size_y, m_position.z() - half_size_z, // bottom right
        m_position.x() - half_size_x, m_position.y() + half_size_y, m_position.z() - half_size_z, // top right

        // Bottom face
        m_position.x() + half_size_x, m_position.y() - half_size_y, m_position.z() + half_size_z, // bottom left
        m_position.x() + half_size_x, m_position.y() - half_size_y, m_position.z() - half_size_z, // bottom right
        m_position.x() - half_size_x, m_position.y() - half_size_y, m_position.z() + half_size_z, // top left

        m_position.x() - half_size_x, m_position.y() - half_size_y, m_position.z() + half_size_z, // top left
        m_position.x() + half_size_x, m_position.y() - half_size_y, m_position.z() - half_size_z, // bottom right
        m_position.x() - half_size_x, m_position.y() - half_size_y, m_position.z() - half_size_z  // top right
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

/* update
 */
void Object3D::update() {

}

/* translate
 */
void Object3D::translate(Eigen::Vector3f direction) {
    glTranslatef(direction.x(), direction.y(), direction.z());
}

/* rotate
 */
void Object3D::rotate(GLfloat angle_deg, Eigen::Vector3f direction) {
    glRotatef(angle_deg, direction.x(), direction.y(), direction.z());
}
