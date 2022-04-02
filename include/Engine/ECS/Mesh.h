#pragma once

// Includes
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

#include <algorithm>
#include <iterator>

#include "Engine/ECS/ECS.h"
#include "Engine/Shader.h"
#include "Engine/Texture.h"

// Enums
typedef enum {
    MATERIAL_COLOR,
    MATERIAL_TEXTURE_2D,
    MATERIAL_TEXTURE_CUBE
} eMaterialType;

typedef enum {
    LIGHT_DIRECTIONAL,
    LIGHT_POINT
} eLightType;

// Structs
typedef struct {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
} Material;

typedef struct {
    eLightType type;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    // Used to calculate attenuation for point lights
    float constant;
    float linear;
    float quadratic;
} Light;

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
        void set_light(Light light);

        bool has_shader() const;
        
        eMaterialType get_material_type() const;

    protected:
        Transform m_transform;

        mat4 m_model;

        Material m_material;
        Light m_light;

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