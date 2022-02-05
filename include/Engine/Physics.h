#pragma once

// Includes
#include "Engine/utils/types.h"
#include "Engine/ECS/ECS.h"
#include "Engine/Object3D.h"

#include "btBulletDynamicsCommon.h"

#include <vector>

// Defines
#define DEG_TO_RAD 0.01745329251994329576923690768489
#define RAD_TO_DEG 57.295779513082320876798154814105

/* Physics
 */
class Physics {
    public:
        Physics();
        virtual ~Physics();

        void add_rigid_body(Object3D *object, float mass);

        void update(float delta_time);

        void cleanup();

    private:
        std::vector<Object3D*> m_objects;

        btDiscreteDynamicsWorld *p_dynamics_world;

        btDefaultCollisionConfiguration *p_collision_configuration;
        btCollisionDispatcher *p_collision_dispatcher;
        btBroadphaseInterface *p_broadphase_interface;
        btSequentialImpulseConstraintSolver *p_constraint_solver;
};