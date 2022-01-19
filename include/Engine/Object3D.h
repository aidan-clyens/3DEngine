#pragma once

// Includes
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <algorithm>
#include <iterator>


// Defines
#define OBJECT3D_CUBE_NUM_FACES         6 * 6
#define OBJECT3D_CUBE_NUM_VERTICES      OBJECT3D_CUBE_NUM_FACES * 3


class Renderer;

/* Object3D
 */
class Object3D {
    friend class Renderer;

    public:
        Object3D(glm::vec3 pos, glm::vec3 rotation, glm::vec3 size);
        virtual ~Object3D();

        void attach_shader(unsigned int program_id);

    protected:
        glm::vec3 m_position;
        glm::vec3 m_rotation;
        glm::vec3 m_size;

        unsigned int m_vertex_buffer_object;
        unsigned int m_vertex_array_object;
        unsigned int m_element_buffer_object;

        unsigned int m_shader_program_id;
};