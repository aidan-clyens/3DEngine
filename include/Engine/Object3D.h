#pragma once

// Includes
#include "Engine/utils/types.h"
#include "Engine/ECS/ECS.h"
#include "Engine/ECS/Mesh.h"


/* Object3D
 */
class Object3D : public Entity {
    public:
        Object3D(vec3 pos, vec3 rotation, vec3 size);
        virtual ~Object3D();

        vec3 get_position() const;
        vec3 get_rotation() const;
        vec3 get_size() const;
        Transform get_transform() const;

        void set_position(vec3 position);
        void set_rotation(vec3 rotation);
        void set_transform(Transform transform);

    protected:
        Transform m_transform;
};