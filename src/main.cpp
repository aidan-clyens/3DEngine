// Includes
#include "Engine/Engine.h"
#include "Engine/Object3D.h"
#include "Engine/Shader.h"

#include <iostream>

// Defines
#define SCREEN_WIDTH 1600
#define SCREEN_HEIGHT 900

#define MOUSE_SENSITIVITY 0.1

// Class definitions
/* Game
 */
class Game : public Engine {
    public:
        /* process_mouse_input
         */
        void process_mouse_input(double x, double y) {
            if (m_first_mouse) {
                m_last_mouse_pos_x = x;
                m_last_mouse_pos_y = y;
                m_first_mouse = false;
            }

            m_mouse_offset_x = x - m_last_mouse_pos_x;
            m_mouse_offset_y = m_last_mouse_pos_y - y;

            m_last_mouse_pos_x = x;
            m_last_mouse_pos_y = y;

            m_mouse_offset_x *= MOUSE_SENSITIVITY;
            m_mouse_offset_y *= MOUSE_SENSITIVITY;

            m_mouse_updated = true;
        }

        /* process_mouse_input
         */
        void process_keyboard_input() {
            const float speed = 2.5 * m_delta_time;

            if (get_key(KEY_W) == KEY_PRESS) {
                m_camera.translate_x(speed);
            }
            if (get_key(KEY_S) == KEY_PRESS) {
                m_camera.translate_x(-speed);
            }
            if (get_key(KEY_A) == KEY_PRESS) {
                m_camera.translate_z(-speed);
            }
            if (get_key(KEY_D) == KEY_PRESS) {
                m_camera.translate_z(speed);
            }
            if (get_key(KEY_SPACE) == KEY_PRESS) {
                m_camera.translate_y(speed);
            }
            if (get_key(KEY_LEFT_SHIFT) == KEY_PRESS) {
                m_camera.translate_y(-speed);
            }

            if (get_key(KEY_ESCAPE) == KEY_PRESS) {
                m_running = false;
            }
        }

        /* process_mouse_input
         */
        void setup() {
            // Load shaders
            Shader shader("shaders/vertex.glsl", "shaders/fragment.glsl");

            // Create objects
            p_cube = new Object3D(glm::vec3(0, 0, 0), m_rotation, glm::vec3(1, 1, 1));
            if (shader.is_valid()) {
                p_cube->attach_shader(shader);
            }

            this->add_object(p_cube);
        }

        /* process_mouse_input
         */
        void update() {
            this->process_keyboard_input();
            
            if (m_mouse_updated) {
                m_camera.set_mouse_offset(m_mouse_offset_x, m_mouse_offset_y);
                m_mouse_updated = false;
            }

            m_rotation.x += m_rotation_speed * m_delta_time;
            m_rotation.y += m_rotation_speed * m_delta_time;

            p_cube->set_rotation(m_rotation);
        }
    
    private:
        Object3D *p_cube;
        glm::vec3 m_rotation = glm::vec3(0, 0, 0);

        double m_rotation_speed = 25;

        // Mouse
        bool m_first_mouse = false;
        double m_last_mouse_pos_x = SCREEN_WIDTH / 2;
        double m_last_mouse_pos_y = SCREEN_HEIGHT / 2;
        double m_mouse_offset_x = 0;
        double m_mouse_offset_y = 0;
        bool m_mouse_updated = false;
};

/* main
 */
int main(int argc, char **argv) {
    Game game;

    if (!game.init()) {
        std::cerr << "Game Engine failed to initialize" << std::endl;
        return -1;
    }

    game.start();
    game.cleanup();

    return 0;
}