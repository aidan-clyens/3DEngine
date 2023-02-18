#include "Engine/DebugWindow.h"
#include "Engine/Engine.h"
#include "Engine/ECS/Mesh.h"


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

        // Components
        DebugWindow::show_components(objects[i]);

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

/* show_components
 */
void DebugWindow::show_components(Object3D *object) {
    // Mesh
    if (object->has_component(COMP_MESH)) {
        Mesh *mesh = (Mesh*)object->get_component(COMP_MESH);

        ImGui::Text("Mesh");

        // Material
        DebugWindow::show_material(mesh);
    }

    // Rigidbody
    if (object->has_component(COMP_RIGIDBODY)) {
        ImGui::Text("Rigidbody");
    }

    // Camera
    if (object->has_component(COMP_CAMERA)) {
        ImGui::Text("Camera");
    }
}

/* show_material
 */
void DebugWindow::show_material(Mesh *mesh) {
    ImGui::Text("Mesh Type: ");
    ImGui::SameLine();

    switch (mesh->get_material_type()) {
        case MATERIAL_COLOR:
            ImGui::Text("Colour");
            break;
        case MATERIAL_TEXTURE_2D:
            ImGui::Text("Texture 2D");
            break;
        case MATERIAL_TEXTURE_CUBE:
            ImGui::Text("Texture Cube");
            break;
        default:
            break;
    }

    Material material = mesh->get_material();

    ImGuiColorEditFlags misc_flags = 0;
    ImVec4 ambient = ImVec4(material.ambient.x, material.ambient.y, material.ambient.z, 1);
    ImVec4 diffuse = ImVec4(material.diffuse.x, material.diffuse.y, material.diffuse.z, 1);
    ImVec4 specular = ImVec4(material.specular.x, material.specular.y, material.specular.z, 1);

    ImGui::Text("Ambient");
    ImGui::SameLine();

    ImGui::PushID("ambient");
    ImGui::ColorEdit3("", (float *)&ambient, misc_flags);
    ImGui::PopID();

    ImGui::Text("Diffuse");
    ImGui::SameLine();

    ImGui::PushID("diffuse");
    ImGui::ColorEdit3("", (float *)&diffuse, misc_flags);
    ImGui::PopID();

    ImGui::Text("Specular");
    ImGui::SameLine();

    ImGui::PushID("specular");
    ImGui::ColorEdit3("", (float *)&specular, misc_flags);
    ImGui::PopID();

    ImGui::Text("Shininess");
    ImGui::SameLine();

    ImGui::PushID("shininess");
    ImGui::DragScalar("", ImGuiDataType_Float, &material.shininess, 0.01f, NULL, NULL, "%.2f");
    ImGui::PopID();

    material.ambient = vec3(ambient.x, ambient.y, ambient.z);
    material.diffuse = vec3(diffuse.x, diffuse.y, diffuse.z);
    material.specular = vec3(specular.x, specular.y, specular.z);

    mesh->set_material(material);
}