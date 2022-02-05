// Includes
#include "Engine/Engine.h"
#include "Engine/CubeMesh.h"
#include "Engine/Shader.h"
#include "Engine/Texture2D.h"
#include "Engine/ECS/Mesh.h"

#include <iostream>

// Defines
#define SCREEN_WIDTH 1600
#define SCREEN_HEIGHT 900

#define WHITE vec3(1, 1, 1)
#define GREY vec3(0.5, 0.5, 0.5)
#define ORANGE vec3(1, 0.5, 0.31)

// Class definitions
/* Game
 */
class Game : public Engine {
    public:
        /* process_mouse_input
         */
        void process_keyboard_input() {
            const float speed = 2.5 * m_delta_time;

            if (p_input_manager->get_key(KEY_W) == KEY_PRESS) {
                p_camera->translate_x(speed);
            }
            if (p_input_manager->get_key(KEY_S) == KEY_PRESS) {
                p_camera->translate_x(-speed);
            }
            if (p_input_manager->get_key(KEY_A) == KEY_PRESS) {
                p_camera->translate_z(-speed);
            }
            if (p_input_manager->get_key(KEY_D) == KEY_PRESS) {
                p_camera->translate_z(speed);
            }
            if (p_input_manager->get_key(KEY_SPACE) == KEY_PRESS) {
                p_camera->translate_y(speed);
            }
            if (p_input_manager->get_key(KEY_LEFT_SHIFT) == KEY_PRESS) {
                p_camera->translate_y(-speed);
            }

            if (p_input_manager->get_key(KEY_ESCAPE) == KEY_PRESS) {
                m_running = false;
            }
        }

        /* setup
         */
        void setup() {
            p_camera->set_position(vec3(0, 0, 3));
            this->set_light_direction(vec3(-1, 1, 0));
            // this->set_mouse_visible(false);

            // Load shaders
            m_shader.load("shaders/vertex.glsl", "shaders/color_fragment.glsl");

            // Configure lighting
            m_material.ambient = GREY;
            m_material.diffuse = GREY;
            m_material.specular = WHITE;
            m_material.shininess = 4;

            m_light.ambient = vec3(0.5, 0.5, 0.5);
            m_light.diffuse = vec3(0.6, 0.6, 0.6);
            m_light.specular = vec3(0.1, 0.1, 0.1);

            // Create ground
            p_ground = new Object3D(vec3(0, -2, 0), vec3(0, 0, 0), vec3(50, 1, 50));
            p_ground->add_component(COMP_MESH, new CubeMesh());

            CubeMesh *mesh = (CubeMesh*)p_ground->get_component(COMP_MESH);
            Transform transform = p_ground->get_transform();

            mesh->set_shader(m_shader);
            mesh->set_material(m_material);
            mesh->set_light(m_light);
            mesh->set_transform(p_ground->get_transform());

            m_physics.add_rigid_body(p_ground, 0);

            this->add_object(p_ground);

            // Create cube
            p_cube = new Object3D(vec3(0, 2, -3), vec3(0, 30, 0), vec3(1, 1, 1));
            p_cube->add_component(COMP_MESH, new CubeMesh());

            Mesh *cube_mesh = (CubeMesh*)p_cube->get_component(COMP_MESH);
            transform = p_cube->get_transform();

            m_material.ambient = ORANGE;
            m_material.diffuse = ORANGE;

            cube_mesh->set_shader(m_shader);
            cube_mesh->set_material(m_material);
            cube_mesh->set_light(m_light);
            cube_mesh->set_transform(p_cube->get_transform());

            m_physics.add_rigid_body(p_cube, 1);

            this->add_object(p_cube);
        }

        /* update
         */
        void update() {
            // this->process_keyboard_input();

            // if (p_input_manager->is_mouse_updated()) {
            //     vec2 mouse_pos = p_input_manager->get_mouse_position();

            //     p_camera->set_mouse_offset(mouse_pos.x, mouse_pos.y);
            //     p_input_manager->set_mouse_handled(true);
            // }
        }
    
    private:
        Object3D *p_ground;
        Object3D *p_cube;

        Shader m_shader;
        Material m_material;
        Light m_light;
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