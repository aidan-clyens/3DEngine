#pragma once

// Includes
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <algorithm>
#include <iterator>

#include "Engine/Shader.h"
#include "Engine/Texture.h"


// Structs
typedef struct {
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
    float shininess;
} Material;

typedef struct {
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
} Light;

typedef struct {
    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 size;
} Transform;

typedef struct {
    float *data;
    unsigned int size;
    unsigned int stride;
} Buffer;

// Forward Declarations
class Renderer;
class Object3DGroup;

/* Object3D
 */
class Object3D {
    friend class Renderer;
    friend class Object3DGroup;

    public:
        Object3D(glm::vec3 pos, glm::vec3 rotation, glm::vec3 size);
        virtual ~Object3D();

        virtual void render();

        glm::vec3 get_position() const;
        glm::vec3 get_rotation() const;
        glm::vec3 get_size() const;
        Transform get_transform() const;

        void set_position(glm::vec3 position);
        void set_rotation(glm::vec3 rotation);
        void set_transform(Transform transform);

        void set_shader(Shader shader);
        void set_texture(Texture texture);
        void set_light(Light light);

        void set_material(Material material);

    protected:
        Transform m_transform;

        glm::mat4 m_model;

        Material m_material;
        Light m_light;

        Buffer m_vertex_buffer;
        Buffer m_normal_buffer;
        Buffer m_uv_buffer;

        unsigned int m_num_vertices;

        unsigned int m_vertex_buffer_object;
        unsigned int m_vertex_array_object;
        unsigned int m_instance_buffer_object;

        bool m_use_texture;

        Shader m_shader;
        Texture m_texture;
};