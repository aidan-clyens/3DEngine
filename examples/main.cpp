// Includes
#include "Engine/Engine.h"
#include "Engine/Object3D.h"
#include "Engine/Shader.h"
#include "Engine/Texture2D.h"

#include <iostream>

// Defines
#define SCREEN_WIDTH 1600
#define SCREEN_HEIGHT 900

#define MOUSE_SENSITIVITY 0.1

#define WHITE glm::vec3(1, 1, 1)
#define ORANGE glm::vec3(1, 0.5, 0.31)

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

        /* setup
         */
        void setup() {
            // Load shaders
            Shader texture_shader("shaders/vertex.glsl", "shaders/texture_fragment.glsl");
            Shader color_shader("shaders/vertex.glsl", "shaders/color_fragment.glsl");

            // Load textures
            Texture2D texture("textures/grass.png", 0);

            // Configure lighting
            LightingData object_lighting;
            object_lighting.color = ORANGE;
            object_lighting.light_color = WHITE;
            object_lighting.ambient_strength = 0.1;
            object_lighting.specular_strength = 0.5;
            object_lighting.shininess = 32;

            LightingData grass_lighting;
            grass_lighting.color = WHITE;
            grass_lighting.light_color = WHITE;
            grass_lighting.ambient_strength = 0.1;
            grass_lighting.specular_strength = 0;
            grass_lighting.shininess = 1;

            // Create light source
            p_light = new Object3D(glm::vec3(2, 2, -5), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1));
            p_light->set_color(WHITE);
            if (color_shader.is_valid()) {
                p_light->attach_shader(color_shader);
            }

            this->add_object(p_light);
            this->add_light(p_light);

            // Create objects
            p_cube1 = new Object3D(glm::vec3(0, -0.5, -1.5), m_rotation, glm::vec3(1, 1, 1));
            p_cube1->set_lighting_data(grass_lighting);
            if (texture_shader.is_valid()) {
                p_cube1->attach_shader(texture_shader);
            }
            p_cube1->attach_texture(texture);

            this->add_object(p_cube1);

            p_cube2 = new Object3D(glm::vec3(-2, -0.5, -1.5), m_rotation, glm::vec3(1, 1, 1));
            p_cube2->set_lighting_data(object_lighting);
            if (color_shader.is_valid()) {
                p_cube2->attach_shader(color_shader);
            }

            this->add_object(p_cube2);

            p_cube3 = new Object3D(glm::vec3(2, -0.5, -1.5), m_rotation, glm::vec3(1, 1, 1));
            p_cube3->set_lighting_data(object_lighting);
            if (color_shader.is_valid()) {
                p_cube3->attach_shader(color_shader);
            }

            this->add_object(p_cube3);
        }

        /* update
         */
        void update() {
            this->process_keyboard_input();
            
            if (m_mouse_updated) {
                m_camera.set_mouse_offset(m_mouse_offset_x, m_mouse_offset_y);
                m_mouse_updated = false;
            }

            m_rotation.x += m_rotation_speed * m_delta_time;
            m_rotation.y += m_rotation_speed * m_delta_time;

            // p_cube1->set_rotation(m_rotation);
            // p_cube2->set_rotation(m_rotation);
            // p_cube3->set_rotation(m_rotation);
        }
    
    private:
        Object3D *p_light;
        Object3D *p_cube1;
        Object3D *p_cube2;
        Object3D *p_cube3;
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