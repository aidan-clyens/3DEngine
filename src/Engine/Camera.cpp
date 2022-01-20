#include "Engine/Camera.h"


/* Camera
 */
Camera::Camera(glm::vec3 position):
m_position(position),
m_front(glm::vec3(0.0, 0.0, -1.0)),
m_up(glm::vec3(0.0, 1.0, 0.0))
{

}

/* set_position
 */
void Camera::set_position(glm::vec3 position) {
    m_position = position;
}

/* translate_x
 */
void Camera::translate_x(float speed) {
    m_position += speed * m_front;
}

/* translate_y
 */
void Camera::translate_y(float speed) {
    m_position += speed * m_up;
}

/* translate_z
 */
void Camera::translate_z(float speed) {
    m_position += speed * glm::normalize(glm::cross(m_front, m_up));
}