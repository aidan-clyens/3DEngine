#include "Engine/Physics.h"


/* Physics
 */
Physics::Physics() {
    p_collision_configuration = new btDefaultCollisionConfiguration();
    p_collision_dispatcher = new btCollisionDispatcher(p_collision_configuration);
    p_broadphase_interface = new btDbvtBroadphase();
    p_constraint_solver = new btSequentialImpulseConstraintSolver();
    p_dynamics_world = new btDiscreteDynamicsWorld(p_collision_dispatcher, p_broadphase_interface, p_constraint_solver, p_collision_configuration);

    p_dynamics_world->setGravity(btVector3(0, -9.8, 0));
}

/* ~Physics
 */
Physics::~Physics() {
    delete p_collision_configuration;
    delete p_collision_dispatcher;
    delete p_broadphase_interface;
    delete p_constraint_solver;
    delete p_dynamics_world;
}

/* add_rigid_body
 */
void Physics::add_rigid_body(Rigidbody *body) {
    m_bodies.push_back(body);
    p_dynamics_world->addRigidBody(body->get_body());
}

/* update
 */
void Physics::update(float delta_time) {
    p_dynamics_world->stepSimulation(delta_time);

    for (int i = 0; i < m_bodies.size(); i++) {
        btCollisionObject *obj = p_dynamics_world->getCollisionObjectArray()[i];
        btRigidBody *body = btRigidBody::upcast(obj);
        btTransform trans;
        if (body && body->getMotionState()) {
            body->getMotionState()->getWorldTransform(trans);
        }
        else {
            trans = obj->getWorldTransform();
        }

        vec3 pos = vec3(float(trans.getOrigin().getX()), float(trans.getOrigin().getY()), float(trans.getOrigin().getZ()));
        btQuaternion q = trans.getRotation();

        vec3 rotation = vec3(0, 0, 0);
        btScalar yaw, pitch, roll;      // Z, Y, X
        q.getEulerZYX(yaw, pitch, roll);
        rotation.x = (float)roll * RAD_TO_DEG;
        rotation.y = (float)pitch * RAD_TO_DEG;
        rotation.z = (float)yaw * RAD_TO_DEG;

        Transform transform;
        transform = m_bodies[i]->get_transform();
        transform.position = pos;
        transform.rotation = rotation;
        m_bodies[i]->set_transform(transform);
    }
}

/* cleanup
 */
void Physics::cleanup() {
    for (int i = p_dynamics_world->getNumCollisionObjects() - 1; i >= 0; i--) {
        btCollisionObject *obj = p_dynamics_world->getCollisionObjectArray()[i];
        btRigidBody *body = btRigidBody::upcast(obj);
        if (body && body->getMotionState()) {
            delete body->getMotionState();
        }
        p_dynamics_world->removeCollisionObject(obj);
        delete obj;
    }
}