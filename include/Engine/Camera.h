#pragma once

// Includes
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


class Renderer;


/* Camera
 */
class Camera {
    friend class Renderer;

    public:
        Camera(glm::vec3 position);

        void translate_x(float speed);
        void translate_y(float speed);
        void translate_z(float speed);

    private:
        glm::vec3 m_position;
        glm::vec3 m_front;
        glm::vec3 m_up;
};