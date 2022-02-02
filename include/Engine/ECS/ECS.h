#pragma once

// Includes
#include <unordered_map>

// Enums
typedef enum {

} eComponentType;

/* Component
 */
class Component {

};

// Typedefs
typedef std::unordered_map<int, Component> ComponentMap;
typedef std::unordered_map<int, Component>::iterator ComponentMapIterator;

/* Entity
 */
class Entity {
    public:
        void add_component(int id, Component component);
        Component get_component(int id);

        bool has_component(int id);

    private:
        ComponentMap m_components;
};