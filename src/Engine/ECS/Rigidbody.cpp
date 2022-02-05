#include "Engine/ECS/Rigidbody.h"


/* Rigidbody
 */
Rigidbody::Rigidbody(Object3D *object, float mass):
p_object(object),
m_mass(btScalar(mass))
{
    Transform transform = p_object->get_transform();

    btCollisionShape *shape = new btBoxShape(btVector3(btScalar(transform.size.x / 2), btScalar(transform.size.y / 2), btScalar(transform.size.z / 2)));
    btTransform new_transform;

    new_transform.setIdentity();
    new_transform.setOrigin(btVector3(transform.position.x, transform.position.y, transform.position.z));
    new_transform.setRotation(btQuaternion(btScalar(transform.rotation.z * DEG_TO_RAD), btScalar(transform.rotation.y * DEG_TO_RAD), btScalar(transform.rotation.x * DEG_TO_RAD)));

    btVector3 inertia(0, 0, 0);
    if (m_mass != 0.f) {
        shape->calculateLocalInertia(m_mass, inertia);
    }

    btDefaultMotionState *motion_state = new btDefaultMotionState(new_transform);
    btRigidBody::btRigidBodyConstructionInfo rb_info(m_mass, motion_state, shape, inertia);
    p_body = new btRigidBody(rb_info);
}

/* set_transform
 */
void Rigidbody::set_transform(Transform transform) {
    p_object->set_transform(transform);
}

/* get_transform
 */
Transform Rigidbody::get_transform() const {
    return p_object->get_transform();
}

/* get_body
 */
btRigidBody *Rigidbody::get_body() {
    return p_body;
}