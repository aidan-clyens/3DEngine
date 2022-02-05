#pragma once

#include "Engine/ECS/ECS.h"
#include "Engine/Object3D.h"

#include "btBulletDynamicsCommon.h"

// Defines
#define DEG_TO_RAD 0.01745329251994329576923690768489
#define RAD_TO_DEG 57.295779513082320876798154814105

/* Rigidbody
 */
class Rigidbody : public Component {
    public:
        Rigidbody(Object3D *object, float mass);

        void set_transform(Transform transform);
        Transform get_transform() const;

        btRigidBody *get_body();

    private:
        btScalar m_mass;
        Object3D *p_object;
        btRigidBody *p_body;
};