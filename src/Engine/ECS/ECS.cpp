#include "Engine/ECS/ECS.h"


/* Entity
 */
Entity::Entity():
p_entity_manager(nullptr)
{

}

/* ~Entity
 */
Entity::~Entity() {

}

/* add_component
 */
void Entity::add_component(int id, Component *component) {
    m_components[id] = component;
    if (p_entity_manager != nullptr) {
        p_entity_manager->handle_add_component(this, component, (eComponentType)id);
    }
}

/* remove_component
 */
void Entity::remove_component(int id) {
    if (this->has_component(id)) {
        if (p_entity_manager != nullptr) {
            p_entity_manager->handle_remove_component(this, m_components[id], (eComponentType)id);
        }
        m_components.erase(id);
    }
}

/* get_component
 */
Component *Entity::get_component(int id) {
    return m_components[id];
}

/* has_component
 */
bool Entity::has_component(int id) {
    return (m_components.find(id) != m_components.end());
}

/* assign_entity_manager
 */
void Entity::assign_entity_manager(EntityManager *manager) {
    p_entity_manager = manager;
}