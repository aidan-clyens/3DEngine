#pragma once

// Includes
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <algorithm>
#include <iterator>

#include "Engine/Shader.h"
#include "Engine/Texture2D.h"


// Defines
#define OBJECT3D_CUBE_NUM_FACES             6
#define OBJECT3D_CUBE_FACE_NUM_VERTICES     6
#define OBJECT3D_CUBE_NUM_VERTICES          OBJECT3D_CUBE_NUM_FACES * OBJECT3D_CUBE_FACE_NUM_VERTICES * 3

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

// Enums
typedef enum {
    CUBE_BACK,
    CUBE_FRONT,
    CUBE_LEFT,
    CUBE_RIGHT,
    CUBE_BOTTOM,
    CUBE_TOP
} eCubeFace;

// Forward Declarations
class Renderer;

/* Object3D
 */
class Object3D {
    friend class Renderer;

    public:
        Object3D(glm::vec3 pos, glm::vec3 rotation, glm::vec3 size);
        virtual ~Object3D();

        glm::vec3 get_position() const;
        glm::vec3 get_rotation() const;
        glm::vec3 get_size() const;

        void set_position(glm::vec3 position);
        void set_rotation(glm::vec3 rotation);

        void set_shader(Shader shader);
        void set_texture(Texture2D texture);
        void set_light(Light light);

        void set_material(Material material);

        void set_face_enabled(eCubeFace face, bool enabled);

    protected:
        glm::vec3 m_position;
        glm::vec3 m_rotation;
        glm::vec3 m_size;

        Material m_material;
        Light m_light;

        unsigned int m_vertex_buffer_object;
        unsigned int m_vertex_array_object;

        bool m_faces_enabled[OBJECT3D_CUBE_NUM_FACES];

        bool m_use_texture;

        Shader m_shader;
        Texture2D m_texture;
};