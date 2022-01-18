#pragma once

// Includes
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <Eigen/Core>

#include <algorithm>
#include <iterator>


// Defines
#define OBJECT3D_CUBE_NUM_FACES         6 * 6
#define OBJECT3D_CUBE_NUM_VERTICES      OBJECT3D_CUBE_NUM_FACES * 3


/* Object3D
 */
class Object3D {
    public:
        Object3D(Eigen::Vector3f pos, Eigen::Vector3f size);

        void render();
        virtual void update();

        void translate(Eigen::Vector3f direction);
        void rotate(GLfloat angle_deg, Eigen::Vector3f direction);

    protected:
        Eigen::Vector3f m_position;
        Eigen::Vector3f m_size;

        unsigned int m_vertex_buffer_object;
        unsigned int m_vertex_array_object;
        unsigned int m_element_buffer_object;
};