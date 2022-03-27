// Includes
#include "Engine/Engine.h"
#include "Engine/SquareMesh.h"
#include "Engine/CubeMesh.h"
#include "Engine/Shader.h"
#include "Engine/Texture2D.h"
#include "Engine/ECS/Mesh.h"

#include <iostream>

// Defines
#define SCREEN_WIDTH 1600
#define SCREEN_HEIGHT 900

#define WHITE vec3(1, 1, 1)
#define GREY vec3(0.4, 0.4, 0.4)
#define ORANGE vec3(1, 0.5, 0.31)
#define BLUE vec3(0, 0.28, 1)

// Class definitions
/* Game
 */
class Game : public Engine {
    public:
        /* process_mouse_input
         */
        void process_keyboard_input() {
            // const float speed = 2.5 * m_delta_time;

            // if (p_input_manager->get_key(KEY_W) == KEY_PRESS) {
            //     p_camera->translate_x(speed);
            // }
            // if (p_input_manager->get_key(KEY_S) == KEY_PRESS) {
            //     p_camera->translate_x(-speed);
            // }
            // if (p_input_manager->get_key(KEY_A) == KEY_PRESS) {
            //     p_camera->translate_z(-speed);
            // }
            // if (p_input_manager->get_key(KEY_D) == KEY_PRESS) {
            //     p_camera->translate_z(speed);
            // }
            // if (p_input_manager->get_key(KEY_SPACE) == KEY_PRESS) {
            //     p_camera->translate_y(speed);
            // }
            // if (p_input_manager->get_key(KEY_LEFT_SHIFT) == KEY_PRESS) {
            //     p_camera->translate_y(-speed);
            // }

            if (p_input_manager->get_key(KEY_ESCAPE) == KEY_PRESS) {
                m_running = false;
            }
        }

        /* setup
         */
        void setup() {
            // this->set_mouse_visible(false);
            p_camera->set_position(vec3(0, 0, 3));
            this->set_light_position(vec3(-2.0f, 4.0f, -1.0f));

            m_texture_2d.load("examples/SimpleCube/res/brick.png");

            // Lighting
            m_light.ambient = vec3(0.5, 0.5, 0.5);
            m_light.diffuse = vec3(0.2, 0.2, 0.2);
            m_light.specular = vec3(0.001, 0.001, 0.001);

            Transform transform;
            transform.position = vec3(0, -2, 0);
            transform.rotation = vec3(0, 0, 0);
            transform.size = vec3(20, 1, 20);

            this->add_object(this->create_cube(transform, GREY, 4));

            // Cube 1
            transform.position = vec3(0, -1, -3);
            transform.rotation = vec3(0, 30, 0);
            transform.size = vec3(1, 1, 1);

            this->add_object(this->create_cube(transform, ORANGE, 4));

            // Cube 2
            transform.position = vec3(2, -1, -4);
            transform.rotation = vec3(0, -10, 0);
            transform.size = vec3(1, 4, 1);

            this->add_object(this->create_cube(transform, BLUE, 4));

            // Square
            transform.position = vec3(0, 0, -4);
            transform.rotation = vec3(0, 0, 0);
            transform.size = vec3(1, 1, 1);

            this->add_object(this->create_square(transform, m_texture_2d));
        }

        /* update
         */
        void update() {
            this->process_keyboard_input();
            
            // if (p_input_manager->is_mouse_updated()) {
            //     vec2 mouse_pos = p_input_manager->get_mouse_position();

            //     p_camera->set_mouse_offset(mouse_pos.x, mouse_pos.y);
            //     p_input_manager->set_mouse_handled(true);
            // }
        }

        /* create_cube
         */
        Object3D *create_cube(Transform transform, vec3 color, int shininess) {
            // Configure material
            Material material;
            material.specular = WHITE;
            material.ambient = color;
            material.diffuse = color;
            material.shininess = shininess;

            // Create object
            Object3D *cube = new Object3D(transform.position, transform.rotation, transform.size);
            cube->add_component(COMP_MESH, new CubeMesh());

            CubeMesh *mesh = (CubeMesh *)cube->get_component(COMP_MESH);

            mesh->set_material(material);
            mesh->set_light(m_light);
            mesh->set_transform(transform);

            return cube;
        }

        /* create_square
         */
        Object3D *create_square(Transform transform, Texture texture) {
            // Create object
            Object3D *square = new Object3D(transform.position, transform.rotation, transform.size);
            square->add_component(COMP_MESH, new SquareMesh());

            SquareMesh *mesh = (SquareMesh *)square->get_component(COMP_MESH);

            mesh->set_texture(texture);
            mesh->set_light(m_light);
            mesh->set_transform(transform);

            return square;
        }

    private:
        Texture2D m_texture_2d;

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