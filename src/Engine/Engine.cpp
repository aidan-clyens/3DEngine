#include "Engine/Engine.h"


/* Engine
 */
Engine::Engine():
m_renderer(SCREEN_WIDTH, SCREEN_HEIGHT, ""),
p_camera(new Camera(vec3(0, 0, 0))),
p_input_manager(InputManager::get_instance())
{

}

/* Engine
 */
Engine::Engine(const std::string &path):
m_renderer(SCREEN_WIDTH, SCREEN_HEIGHT, path),
p_camera(new Camera(vec3(0, 0, 0))),
p_input_manager(InputManager::get_instance())
{

}

Engine::~Engine() {

}

/* init
 */
bool Engine::init() {
    if (!m_renderer.init(this)) {
        std::cerr << "Failed to init Renderer" << std::endl;
        m_renderer.close();
        return false;
    }

    glfwSetWindowUserPointer(m_renderer.get_window(), this);

    p_input_manager->set_render_window(m_renderer.get_window());
    p_input_manager->set_screen_dimensions(SCREEN_WIDTH, SCREEN_HEIGHT);

    m_renderer.set_mouse_button_callback(this->_process_mouse_button);
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

        m_physics.update(m_delta_time);
        m_renderer.render(m_meshes, *p_camera);
    }
}

/* cleanup
 */
void Engine::cleanup() {
    for (Object3D *object : m_objects) {
        delete object;
    }

    m_physics.cleanup();
    m_renderer.close();
}

/* add_object
 */
void Engine::add_object(Object3D *object) {
    m_objects.push_back(object);

    if (object->has_component(COMP_MESH)) {
        m_meshes.push_back((Mesh*)object->get_component(COMP_MESH));
    }

    if (object->has_component(COMP_RIGIDBODY)) {
        m_physics.add_rigid_body((Rigidbody*)object->get_component(COMP_RIGIDBODY));
    }
}

/* get_objects
 */
void Engine::get_objects(std::vector<Object3D *> &objects) {
    objects = m_objects;
}

/* set_directional_light
 */
void Engine::set_directional_light(DirectionalLight light) {
    m_renderer.set_directional_light(light);
}

/* add_light
 */
void Engine::add_light(PointLight light) {
    m_renderer.add_light(light);
}

/* remove_light
 */
bool Engine::remove_light(int id) {
    return m_renderer.remove_light(id);
}

/* set_background_color
 */
void Engine::set_background_color(vec3 color) {
    m_renderer.set_background_color(color);
}

/* set_skybox
 */
void Engine::set_skybox(Object3D *skybox) {
    m_renderer.set_skybox(skybox);
}

/* set_camera
 */
void Engine::set_camera(Camera *camera) {
    delete p_camera;
    p_camera = camera;
}

/* set_mouse_visible
 */
void Engine::set_mouse_visible(bool value) {
    m_renderer.set_mouse_visible(value);
}

/* set_shadows_enabled
 */
void Engine::set_shadows_enabled(bool enable) {
    m_renderer.set_shadows_enabled(enable);
}

/* set_debug_window_enabled
 */
void Engine::set_debug_window_enabled(bool enable) {
    m_renderer.set_debug_window_enabled(enable);
}

/* setup
 */
void Engine::setup() {

}

/* update
 */
void Engine::update() {

}

/* process_mouse_button
 */
void Engine::process_mouse_button(int button, int action, int mods) {
    DebugWindow::add_mouse_button_event(button, action);
}

/* process_mouse_input
 */
void Engine::process_mouse_input(double x, double y) {
    p_input_manager->process_mouse_input(x, y);
}

/* get_renderer
 */
Renderer *Engine::get_renderer() {
    return &m_renderer;
}

/* _process_mouse_button
 */
void Engine::_process_mouse_button(GLFWwindow *window, int button, int action, int mods) {
    Engine *engine = static_cast<Engine*>(glfwGetWindowUserPointer(window));
    engine->process_mouse_button(button, action, mods);
}

/* _process_mouse_input
 */
void Engine::_process_mouse_input(GLFWwindow *window, double x, double y) {
    Engine *engine = static_cast<Engine*>(glfwGetWindowUserPointer(window));
    engine->process_mouse_input(x, y);
}