#pragma once

// Includes
#include <glm/gtc/matrix_transform.hpp>

#include "Engine/utils/types.h"


class Renderer;


/* Camera
 */
class Camera {
    friend class Renderer;

    public:
        Camera(vec3 position);

        void set_position(vec3 position);

        void set_mouse_offset(double offset_x, double offset_y);

        void translate_x(float speed);
        void translate_y(float speed);
        void translate_z(float speed);

    private:
        vec3 m_position;
        vec3 m_front;
        vec3 m_up;

        double m_yaw;
        double m_pitch;
};