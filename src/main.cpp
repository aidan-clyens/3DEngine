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


// Global Variables
double delta_time = 0;


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
    const float speed = 1.0 * delta_time;

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        camera.translate_y(speed);
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        camera.translate_y(-speed);
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        camera.translate_z(-speed);
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        camera.translate_z(speed);
    }
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
    while (!renderer.is_window_closed()) {
        current_frame = glfwGetTime();
        delta_time = current_frame - last_frame;
        last_frame = current_frame;

        process_input(renderer.get_window(), camera);

        rotation.x += rotation_speed * delta_time;
        rotation.y += rotation_speed * delta_time;

        cube->set_rotation(rotation);

        camera.set_position(glm::vec3(sin(current_frame) * radius, 0.0, cos(current_frame) * radius));

        renderer.render(objects, camera);
    }

    for (Object3D *object : objects) {
        delete object;
    }

    renderer.close();

    return 0;
}
