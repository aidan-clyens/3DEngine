#pragma once

// Includes
#include "Engine/Renderer.h"
#include "Engine/Object3D.h"
#include "Engine/Camera.h"

#include <vector>
#include <iostream>

// Defines
#define SCREEN_WIDTH 1600
#define SCREEN_HEIGHT 900

#define MOUSE_SENSITIVITY 0.1

// Enums
/* eKey
 */
typedef enum {
    KEY_W           = GLFW_KEY_W,
    KEY_S           = GLFW_KEY_S,
    KEY_A           = GLFW_KEY_A,
    KEY_D           = GLFW_KEY_D,
    KEY_SPACE       = GLFW_KEY_SPACE,
    KEY_LEFT_SHIFT  = GLFW_KEY_LEFT_SHIFT,
    KEY_ESCAPE      = GLFW_KEY_ESCAPE
} eKey;

/* eKeyAction
 */
typedef enum {
    KEY_PRESS       = GLFW_PRESS,
    KEY_REPEAT      = GLFW_REPEAT,
    KEY_RELEASE     = GLFW_RELEASE
} eKeyAction;


/* Engine
 */
class Engine {
    public:
        Engine();

        bool init();
        void start();
        void cleanup();

        void add_object(Object3D *object);

        void set_light_direction(glm::vec3 direction);

        eKeyAction get_key(eKey key);

        // To be implemented by user
        virtual void setup();
        virtual void update();

        virtual void process_mouse_input(double x, double y);

    protected:
        Camera m_camera;
        double m_delta_time;
        bool m_running;

    private:
        void static _process_mouse_input(GLFWwindow *window, double x, double y);

        Renderer m_renderer;

        glm::vec3 m_light_direction;

        std::vector<Object3D*> m_objects;
};