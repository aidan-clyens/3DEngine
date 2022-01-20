// Includes
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <vector>

#include "Engine/Renderer.h"
#include "Engine/Object3D.h"
#include "Engine/ShaderLoader.h"
#include "Engine/Camera.h"


// Defines
#define SCREEN_WIDTH        1600
#define SCREEN_HEIGHT       900

#define MOUSE_SENSITIVITY   0.1


// Global Variables
bool running = false;
double delta_time = 0;

bool first_mouse = false;;
double last_mouse_pos_x = SCREEN_WIDTH / 2;
double last_mouse_pos_y = SCREEN_HEIGHT / 2;
double mouse_offset_x = 0;
double mouse_offset_y = 0;
bool mouse_updated = false;


// Class definitions
/* Cube
 */
class Cube : public Object3D {
    public:
        Cube(glm::vec3 pos, glm::vec3 rotation, float width):
        Object3D(pos, rotation, glm::vec3(width, width, width))
        {

        }
};

/* process_input
 */
void process_input(GLFWwindow *window, Camera &camera) {
    const float speed = 2.5 * delta_time;

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        camera.translate_x(speed);
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        camera.translate_x(-speed);
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        camera.translate_z(-speed);
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        camera.translate_z(speed);
    }
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
        camera.translate_y(speed);
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
        camera.translate_y(-speed);
    }

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        running = false;
    }
}

/* process_input
 */
void process_mouse_input(GLFWwindow *window, double x, double y) {
    if (first_mouse) {
        last_mouse_pos_x = x;
        last_mouse_pos_y = y;
        first_mouse = false;
    }

    mouse_offset_x = x - last_mouse_pos_x;
    mouse_offset_y = last_mouse_pos_y - y;

    last_mouse_pos_x = x;
    last_mouse_pos_y = y;

    mouse_offset_x *= MOUSE_SENSITIVITY;
    mouse_offset_y *= MOUSE_SENSITIVITY;

    mouse_updated = true;
}

/* main
 */
int main(int argc, char **argv) {
    Renderer renderer(SCREEN_WIDTH, SCREEN_HEIGHT);
    ShaderLoader shader_loader;
    Camera camera(glm::vec3(0.0, 0.0, 3.0));

    if (!renderer.init()) {
        std::cerr << "Failed to init Renderer" << std::endl;
        renderer.close();
        return -1;
    }

    renderer.set_mouse_callback(process_mouse_input);

    // Load shaders
    unsigned int vertex_shader_id;
    unsigned int fragment_shader_id;
    unsigned int shader_program_id;
    if (shader_loader.load_shader("shaders/vertex.glsl", SHADER_VERTEX, vertex_shader_id) &&
        shader_loader.load_shader("shaders/fragment.glsl", SHADER_FRAGMENT, fragment_shader_id)) {

        shader_loader.link_shader_program(vertex_shader_id, fragment_shader_id, shader_program_id);
    }

    // Create objects
    std::vector<Object3D*> objects;

    glm::vec3 rotation = glm::vec3(0, 0, 0);

    Cube *cube = new Cube(glm::vec3(0, 0, -2), rotation, 1);
    cube->attach_shader(shader_program_id);
    objects.push_back(cube);

    double radius = 10;
    double rotation_speed = 25;

    // Main rendering loop
    double current_frame = 0;
    double last_frame = 0;
    running = true;
    while (!renderer.is_window_closed() && running) {
        current_frame = glfwGetTime();
        delta_time = current_frame - last_frame;
        last_frame = current_frame;

        process_input(renderer.get_window(), camera);

        if (mouse_updated) {
            camera.set_mouse_offset(mouse_offset_x, mouse_offset_y);
            mouse_updated = false;
        }

        rotation.x += rotation_speed * delta_time;
        rotation.y += rotation_speed * delta_time;

        cube->set_rotation(rotation);

        // camera.set_position(glm::vec3(sin(current_frame) * radius, 0.0, cos(current_frame) * radius));

        renderer.render(objects, camera);
    }

    for (Object3D *object : objects) {
        delete object;
    }

    renderer.close();

    return 0;
}
