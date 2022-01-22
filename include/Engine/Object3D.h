#pragma once

// Includes
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <algorithm>
#include <iterator>

#include "Engine/Shader.h"


// Defines
#define OBJECT3D_CUBE_NUM_FACES         6 * 6
#define OBJECT3D_CUBE_NUM_VERTICES      OBJECT3D_CUBE_NUM_FACES * 3

// Structs
typedef struct {
    glm::vec3 color;
    glm::vec3 light_color;
    float ambient_strength;
} LightingData;

// Forward Declarations
class Renderer;

/* Object3D
 */
class Object3D {
    friend class Renderer;

    public:
        Object3D(glm::vec3 pos, glm::vec3 rotation, glm::vec3 size);
        virtual ~Object3D();

        void set_position(glm::vec3 position);
        void set_rotation(glm::vec3 rotation);

        void attach_shader(Shader shader);

        void set_lighting_data(LightingData data);
        void set_color(glm::vec3 color);
        void set_light_color(glm::vec3 color);

    protected:
        glm::vec3 m_position;
        glm::vec3 m_rotation;
        glm::vec3 m_size;

        LightingData m_lighting_data;

        unsigned int m_vertex_buffer_object;
        unsigned int m_vertex_array_object;
        unsigned int m_element_buffer_object;

        Shader m_shader;
};