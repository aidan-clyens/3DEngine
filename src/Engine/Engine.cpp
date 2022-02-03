#include "Engine/Engine.h"


/* Engine
 */
Engine::Engine():
m_renderer(SCREEN_WIDTH, SCREEN_HEIGHT),
p_input_manager(InputManager::get_instance()),
m_camera(vec3(0.0, 0.0, 3.0)),
m_light_direction(vec3(0.4, 0.5, -0.6))
{

}

/* init
 */
bool Engine::init() {
    if (!m_renderer.init()) {
        std::cerr << "Failed to init Renderer" << std::endl;
        m_renderer.close();
        return false;
    }

    glfwSetWindowUserPointer(m_renderer.get_window(), this);

    p_input_manager->set_render_window(m_renderer.get_window());
    p_input_manager->set_screen_dimensions(SCREEN_WIDTH, SCREEN_HEIGHT);

    m_renderer.set_mouse_callback(this->_process_mouse_input);

    return true;
}

/* start
 */
void Engine::start() {
    this->setup();

    // Main rendering loop
    double current_frame = 0;
    double last_frame = 0;
    m_running = true;
    while (!m_renderer.is_window_closed() && m_running) {
        current_frame = glfwGetTime();
        m_delta_time = current_frame - last_frame;
        last_frame = current_frame;

        this->update();

        m_renderer.render(m_objects, m_camera, m_light_direction);
    }
}

/* cleanup
 */
void Engine::cleanup() {
    for (Object3D *object : m_objects) {
        delete object;
    }

    m_renderer.close();
}

/* add_object
 */
void Engine::add_object(Object3D *object) {
    m_objects.push_back(object);
}

/* set_light_direction
 */
void Engine::set_light_direction(vec3 direction) {
    m_light_direction = direction;
}

/* setup
 */
void Engine::setup() {

}

/* update
 */
void Engine::update() {

}

/* process_mouse_input
 */
void Engine::process_mouse_input(double x, double y) {
    p_input_manager->process_mouse_input(x, y);
}

/* _process_mouse_input
 */
void Engine::_process_mouse_input(GLFWwindow *window, double x, double y) {
    Engine *engine = static_cast<Engine*>(glfwGetWindowUserPointer(window));
    engine->process_mouse_input(x, y);
}