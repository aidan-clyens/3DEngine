#pragma once

// Includes
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

#include <algorithm>
#include <iterator>

#include "Engine/utils/types.h"
#include "Engine/ECS/ECS.h"
#include "Engine/Shader.h"
#include "Engine/Texture.h"


typedef struct {
    float *data;
    unsigned int size;
    unsigned int stride;
} Buffer;

// Forward Declarations
class Renderer;
class MeshInstances;

/* Mesh
 */
class Mesh : public Component {
    friend class Renderer;
    friend class MeshInstances;

    public:
        Mesh();
        virtual ~Mesh();

        virtual void render();

        void set_transform(Transform transform);

        void set_shader(Shader shader);
        void set_texture(Texture texture);
        void set_material(Material material);

        Material get_material() const;

        bool has_shader() const;
        
        eMaterialType get_material_type() const;

    protected:
        Transform m_transform;

        mat4 m_model;

        Material m_material;

        Buffer m_vertex_buffer;
        Buffer m_normal_buffer;
        Buffer m_uv_buffer;

        unsigned int m_num_vertices;

        unsigned int m_vertex_buffer_object;
        unsigned int m_vertex_array_object;
        unsigned int m_instance_buffer_object;

        bool m_use_shader;
        bool m_use_texture;

        Shader m_shader;
        Texture m_texture;

        eMaterialType m_material_type;
};