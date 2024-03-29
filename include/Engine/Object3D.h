#pragma once

// Includes
#include "Engine/utils/types.h"
#include "Engine/ECS/ECS.h"
#include "Engine/ECS/Mesh.h"
#include "Engine/Light.h"

#include <string>

/* Object3D
 */
class Object3D : public Entity {
    public:
        Object3D();
        Object3D(vec3 pos, vec3 rotation, vec3 size);
        virtual ~Object3D();

        vec3 get_position() const;
        vec3 get_rotation() const;
        vec3 get_size() const;
        Transform get_transform() const;

        void set_position(vec3 position);
        void set_rotation(vec3 rotation);
        void set_size(vec3 size);
        void set_transform(Transform transform);

        std::string get_name() const;
        void set_name(const std::string &name);

    protected:
        Transform m_transform;
        std::string m_name; 
};