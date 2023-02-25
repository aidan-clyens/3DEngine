#include "Engine/Object3D.h"


/* Object3D
 */
Object3D::Object3D() {
    // Initialize transform
    m_transform.position = vec3(0.0f, 0.0f, 0.0f);
    m_transform.rotation = vec3(0.0f, 0.0f, 0.0f);
    m_transform.size = vec3(1.0f, 1.0f, 1.0f);
}

/* Object3D
 */
Object3D::Object3D(vec3 pos, vec3 rotation, vec3 size) {
    // Initialize transform
    m_transform.position = pos;
    m_transform.rotation = rotation;
    m_transform.size = size;
}

/* ~Object3D
 */
Object3D::~Object3D() {

}

/* get_position
 */
vec3 Object3D::get_position() const {
    return m_transform.position;
}

/* get_rotation
 */
vec3 Object3D::get_rotation() const {
    return m_transform.rotation;
}

/* get_size
 */
vec3 Object3D::get_size() const {
    return m_transform.size;
}

/* get_transform
 */
Transform Object3D::get_transform() const {
    return m_transform;
}

/* set_position
 */
void Object3D::set_position(vec3 position) {
    m_transform.position = position;
    this->set_transform(m_transform);
}

/* set_rotation
 */
void Object3D::set_rotation(vec3 rotation) {
    m_transform.rotation = rotation;
    this->set_transform(m_transform);
}

/* set_size
 */
void Object3D::set_size(vec3 size) {
    m_transform.size = size;
    this->set_transform(m_transform);
}

/* set_transform
 */
void Object3D::set_transform(Transform transform) {
    m_transform = transform;

    if (this->has_component(COMP_MESH)) {
        Mesh *mesh = (Mesh*)this->get_component(COMP_MESH);
        mesh->set_transform(m_transform);
    }
}