#include "Engine/DebugWindow.h"
#include "Engine/Engine.h"

Engine *DebugWindow::p_engine = nullptr;

/* init
 */
void DebugWindow::init(Engine *engine) {
    p_engine = engine;

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

    ImGui::StyleColorsDark();

    const char *glsl_version = "#version 330";
    ImGui_ImplGlfw_InitForOpenGL(engine->get_renderer()->get_window(), true);
    ImGui_ImplOpenGL3_Init(glsl_version);
}

/* close
 */
void DebugWindow::close() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

/* create_window
 */
void DebugWindow::create_window() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    bool show_window = true;
    // ImGui::ShowDemoWindow(&show_window);
    DebugWindow::show_window(&show_window);
}

/* render
 */
void DebugWindow::render() {
    ImGui::Render();
}

/* render_draw_data
 */
void DebugWindow::render_draw_data() {
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

/* add_mouse_button_event
 */
void DebugWindow::add_mouse_button_event(int button, int action) {
    ImGuiIO &io = ImGui::GetIO();
    io.AddMouseButtonEvent(button, (action == 1));
}

/* want_capture_mouse
 */
bool DebugWindow::want_capture_mouse() {
    ImGuiIO &io = ImGui::GetIO();
    return io.WantCaptureMouse;
}

/* show_window
 */
void DebugWindow::show_window(bool *open) {
    ImGuiWindowFlags window_flags = 0;
    if (!ImGui::Begin("3D Engine", open, window_flags)) {
        ImGui::End();
        return;
    }

    // Objects
    if (ImGui::CollapsingHeader("Objects")) {
        std::vector<Object3D*> objects;
        p_engine->get_objects(objects);

        for (int i = 0; i < objects.size(); i++) {
            ImGui::Text(std::to_string(i).c_str());
        }
    }

    ImGui::End();
}
