#pragma once

// Includes
#include "Engine/utils/types.h"

#include <unordered_map>

// Enums
typedef enum {
    COMP_MESH = 0,
    COMP_RIGIDBODY = 1,
    COMP_CAMERA = 2
} eComponentType;

// Structs
typedef struct {
    vec3 position;
    vec3 rotation;
    vec3 size;
} Transform;

// Forward Declarations
class Entity;

/* Component
 */
class Component {

};

/* EntityManager
 */
class EntityManager {
    public:
        virtual void handle_add_component(Entity *entity, Component *component, eComponentType type) = 0;
};

// Typedefs
typedef std::unordered_map<int, Component*> ComponentMap;
typedef std::unordered_map<int, Component*>::iterator ComponentMapIterator;

/* Entity
 */
class Entity {
    public:
        Entity();
        virtual ~Entity();

        void add_component(int id, Component *component);
        Component *get_component(int id);

        bool has_component(int id);

        void assign_entity_manager(EntityManager *manager);

    private:
        EntityManager *p_entity_manager;
        ComponentMap m_components;
};