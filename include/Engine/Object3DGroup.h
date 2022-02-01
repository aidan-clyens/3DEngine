#pragma once

// Includes
#include "Engine/utils/types.h"
#include "Engine/Object3D.h"

#include <vector>

/* Object3DGroup
 */
class Object3DGroup : public Object3D {
    public:
        Object3DGroup(Object3D *instance);
        Object3DGroup(Object3D *instance, std::vector<Transform> transforms);
        virtual ~Object3DGroup();

        void render();

        void add_transform(Transform transform);
    
    private:
        Object3D *m_instance;
        std::vector<mat4> m_models;
        int m_num_vertices;
};