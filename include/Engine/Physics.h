#pragma once

// Includes
#include "Engine/utils/types.h"
#include "Engine/ECS/ECS.h"
#include "Engine/ECS/Rigidbody.h"
#include "Engine/Object3D.h"

#include "btBulletDynamicsCommon.h"

#include <vector>

/* Physics
 */
class Physics {
    public:
        Physics();
        virtual ~Physics();

        void add_rigid_body(Rigidbody *body);

        void update(float delta_time);

        void cleanup();

    private:
        std::vector<Rigidbody*> m_bodies;

        btDiscreteDynamicsWorld *p_dynamics_world;

        btDefaultCollisionConfiguration *p_collision_configuration;
        btCollisionDispatcher *p_collision_dispatcher;
        btBroadphaseInterface *p_broadphase_interface;
        btSequentialImpulseConstraintSolver *p_constraint_solver;
};