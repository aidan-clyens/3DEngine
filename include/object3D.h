#pragma once

// Includes
#include <GL/glew.h>
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
        Object3D(Eigen::Vector3f pos, GLfloat width);

        void render();

    private:
        Eigen::Vector3f m_position;
        GLfloat m_width;
        GLfloat m_vertices[OBJECT3D_CUBE_NUM_VERTICES];
};