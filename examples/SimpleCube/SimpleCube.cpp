// Includes
#include "Engine/Engine.h"
#include "Engine/SquareMesh.h"
#include "Engine/CubeMesh.h"
#include "Engine/Shader.h"
#include "Engine/Texture2D.h"
#include "Engine/TextureCubeMap.h"
#include "Engine/Light.h"
#include "Engine/ECS/Mesh.h"
#include "Engine/utils/Timer.h"

#include <iostream>

// Defines
#define SCREEN_WIDTH 1600
#define SCREEN_HEIGHT 900

#define WHITE vec3(1, 1, 1)
#define GREY vec3(0.4, 0.4, 0.4)
#define ORANGE vec3(1, 0.5, 0.31)
#define BLUE vec3(0, 0.28, 1)


static bool key_ready = true;


// Class definitions
/* Game
 */
class Game : public Engine {
    public:
        /* process_mouse_input
         */
        void process_keyboard_input() {
            const float speed = 2.5 * m_delta_time;

            if (!m_mouse_enabled) {
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
            }

            if (p_input_manager->get_key(KEY_ESCAPE) == KEY_PRESS) {
                if (key_ready) {
                    m_mouse_enabled = !m_mouse_enabled;
                    this->set_mouse_visible(m_mouse_enabled);
                    Timer([]() { key_ready = true; }, 100);
                }
            }
        }

        /* setup
         */
        void setup() {
            m_mouse_enabled = false;

            this->set_mouse_visible(m_mouse_enabled);
            this->set_shadows_enabled(true);

            p_camera->set_position(vec3(0, 0, 3));

            // Load textures
            m_texture_2d.load("examples/SimpleCube/res/brick.png");

            std::vector<std::string> faces;
            for (int i = 0; i < 6; i++) {
                faces.push_back("examples/SimpleCube/res/brick.png");
            }
            m_texture_cube.load(faces);

            // Lighting
            PointLight light1;
            light1.set_position(vec3(-1.0, 0.0, 2.0));
            light1.set_lighting(vec3(0.5, 0.5, 0.5), vec3(0.5, 0.5, 0.5), vec3(0.2, 0.2, 0.2));
            light1.set_light_strength(LIGHT_DISTANCE_32);

            this->add_light(light1);

            PointLight light2;
            light2.set_position(vec3(5.0, 0.0, -5.0));
            light2.set_lighting(vec3(0.5, 0.5, 0.5), vec3(0.5, 0.5, 0.5), vec3(0.2, 0.2, 0.2));
            light2.set_light_strength(LIGHT_DISTANCE_7);

            this->add_light(light2);

            Transform transform;
            transform.position = vec3(0, -2, 0);
            transform.rotation = vec3(0, 0, 0);
            transform.size = vec3(20, 1, 20);

            this->add_object(this->create_cube(transform, GREY, 4));

            // Cube 1
            transform.position = vec3(0, -1, -3);
            transform.rotation = vec3(0, 30, 0);
            transform.size = vec3(1, 1, 1);

            this->add_object(this->create_cube(transform, m_texture_cube));

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

            if (!m_mouse_enabled) {
                if (p_input_manager->is_mouse_updated()) {
                    vec2 mouse_pos = p_input_manager->get_mouse_position();

                    p_camera->set_mouse_offset(mouse_pos.x, mouse_pos.y);
                    p_input_manager->set_mouse_handled(true);
                }
            }
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
            mesh->set_transform(transform);

            return cube;
        }

        /* create_cube
         */
        Object3D *create_cube(Transform transform, Texture texture) {
            // Create object
            Object3D *cube = new Object3D(transform.position, transform.rotation, transform.size);
            cube->add_component(COMP_MESH, new CubeMesh());

            CubeMesh *mesh = (CubeMesh *)cube->get_component(COMP_MESH);

            mesh->set_texture(texture);
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
            mesh->set_transform(transform);

            return square;
        }

    private:
        Texture2D m_texture_2d;
        TextureCubeMap m_texture_cube;

        bool m_mouse_enabled;
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