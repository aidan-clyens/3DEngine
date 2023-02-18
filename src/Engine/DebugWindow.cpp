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
        DebugWindow::show_objects();
    }

    ImGui::End();
}

/* show_objects
 */
void DebugWindow::show_objects() {
    std::vector<Object3D*> objects;
    p_engine->get_objects(objects);


    ImGui::PushID("show objects");
    for (int i = 0; i < objects.size(); i++) {
        ImGui::PushID(i);
        ImGui::Text("Object %d", i);

        // Transform
        DebugWindow::show_transform(objects[i]);

        ImGui::Separator();
        ImGui::PopID();
    }
    ImGui::PopID();
}

/* show_transform
 */
void DebugWindow::show_transform(Object3D *object) {
    // Transform
    vec3 position = object->get_position();
    vec3 rotation = object->get_rotation();
    vec3 size = object->get_size();

    if (ImGui::BeginTable("Transform", 4)) {
        // Position
        ImGui::TableNextRow();
        ImGui::TableNextColumn();
        ImGui::Text("Position");
        ImGui::TableNextColumn();

        ImGui::PushID("position x");
        ImGui::DragScalar("", ImGuiDataType_Float, &position.x, 0.01f, NULL, NULL, "%.2f");
        ImGui::PopID();

        ImGui::TableNextColumn();

        ImGui::PushID("position y");
        ImGui::DragScalar("", ImGuiDataType_Float, &position.y, 0.01f, NULL, NULL, "%.2f");
        ImGui::PopID();

        ImGui::TableNextColumn();

        ImGui::PushID("position z");
        ImGui::DragScalar("", ImGuiDataType_Float, &position.z, 0.01f, NULL, NULL, "%.2f");
        ImGui::PopID();

        // Rotation
        ImGui::TableNextRow();
        ImGui::TableNextColumn();
        ImGui::Text("Rotation");
        ImGui::TableNextColumn();

        ImGui::PushID("rotation x");
        ImGui::DragScalar("", ImGuiDataType_Float, &rotation.x, 1.0f, NULL, NULL, "%.2f");
        ImGui::PopID();

        ImGui::TableNextColumn();

        ImGui::PushID("rotation y");
        ImGui::DragScalar("", ImGuiDataType_Float, &rotation.y, 1.0f, NULL, NULL, "%.2f");
        ImGui::PopID();

        ImGui::TableNextColumn();

        ImGui::PushID("rotation z");
        ImGui::DragScalar("", ImGuiDataType_Float, &rotation.z, 1.0f, NULL, NULL, "%.2f");
        ImGui::PopID();

        // Size
        ImGui::TableNextRow();
        ImGui::TableNextColumn();
        ImGui::Text("Size");
        ImGui::TableNextColumn();

        ImGui::PushID("size x");
        ImGui::DragScalar("", ImGuiDataType_Float, &size.x, 0.01f, NULL, NULL, "%.2f");
        ImGui::PopID();

        ImGui::TableNextColumn();

        ImGui::PushID("size y");
        ImGui::DragScalar("", ImGuiDataType_Float, &size.y, 0.01f, NULL, NULL, "%.2f");
        ImGui::PopID();

        ImGui::TableNextColumn();

        ImGui::PushID("size z");
        ImGui::DragScalar("", ImGuiDataType_Float, &size.z, 0.01f, NULL, NULL, "%.2f");
        ImGui::PopID();

        ImGui::EndTable();
    }

    object->set_position(position);
    object->set_rotation(rotation);
    object->set_size(size);
}