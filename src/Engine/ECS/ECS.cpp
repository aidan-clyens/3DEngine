#include "Engine/ECS/ECS.h"


/* add_component
 */
void Entity::add_component(int id, Component component) {
    m_components[id] = component;
}

/* get_component
 */
Component Entity::get_component(int id) {
    return m_components[id];
}

/* has_component
 */
bool Entity::has_component(int id) {
    return (m_components.find(id) != m_components.end());
}