#include "Engine/DebugWindow.h"
#include "Engine/Engine.h"
#include "Engine/ECS/Mesh.h"
#include "Engine/CubeMesh.h"
#include "Engine/Light.h"


#define BUTTON_SIZE ImVec2(100, 25)


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

    // Scene
    if (ImGui::CollapsingHeader("Scene")) {
        DebugWindow::show_scene();
    }

    // Objects
    if (ImGui::CollapsingHeader("Objects")) {
        DebugWindow::show_objects();

        if (ImGui::Button("New Object", BUTTON_SIZE)) {
            p_engine->add_object(new Object3D());
        }
    }

    ImGui::End();
}

/* show_scene
 */
void DebugWindow::show_scene() {
    // Camera
    ImGui::PushID("show camera");
    ImGui::Text("Main Camera");

    Camera *camera = p_engine->get_camera();

    vec3 camera_position = camera->get_position();

    // Position
    ImGui::Text("Position");
    ImGui::SameLine();

    ImGui::PushID("position");
    camera_position = DebugWindow::show_vec3(camera_position);
    ImGui::PopID();

    camera->set_position(camera_position);

    ImGui::Separator();
    ImGui::PopID();

    // Directional Light
    ImGui::PushID("show directional light");
    ImGui::Text("Directional Light");

    DirectionalLight directional_light = p_engine->get_directional_light();
    vec3 position = directional_light.get_position();
    vec3 origin = directional_light.get_origin();

    // Position
    ImGui::Text("Position");
    ImGui::SameLine();

    ImGui::PushID("position");
    position = DebugWindow::show_vec3(position);
    ImGui::PopID();

    // Origin
    ImGui::Text("Origin");
    ImGui::SameLine();

    ImGui::PushID("origin");
    origin = DebugWindow::show_vec3(origin);
    ImGui::PopID();

    DebugWindow::show_light(&directional_light);

    directional_light.set_position(position);
    directional_light.set_origin(origin);
    p_engine->set_directional_light(directional_light);

    ImGui::Separator();
    ImGui::PopID();
}

/* show_objects
 */
void DebugWindow::show_objects() {
    std::vector<Object3D*> objects;
    p_engine->get_objects(objects);

    ImGui::PushID("show objects");
    for (int i = 0; i < objects.size(); i++) {
        // char name[50];
        // sprintf(name, "Object %d", i);

        std::string name = objects[i]->get_name();

        ImGui::PushID(i);
        if (ImGui::TreeNode(name.c_str())) {
            // Transform
            DebugWindow::show_transform(objects[i]);

            ImGui::Separator();

            // Components
            DebugWindow::show_components(objects[i]);

            // Delete Object Button
            if (ImGui::Button("Delete Object", BUTTON_SIZE)) {
                p_engine->remove_object(objects[i]);
            }

            ImGui::Separator();
            ImGui::TreePop();
        }
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

    // Position
    ImGui::Text("Position");
    ImGui::SameLine();

    ImGui::PushID("position");
    position = DebugWindow::show_vec3(position);
    ImGui::PopID();

    // Rotation
    ImGui::Text("Rotation");
    ImGui::SameLine();

    ImGui::PushID("rotation");
    rotation = DebugWindow::show_vec3(rotation, 1.0f);
    ImGui::PopID();

    // Size
    ImGui::Text("Size");
    ImGui::SameLine();

    ImGui::PushID("size");
    size = DebugWindow::show_vec3(size);
    ImGui::PopID();

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

        if (ImGui::Button("Delete Mesh", BUTTON_SIZE)) {
            object->remove_component(COMP_MESH);
        }
    }
    else {
        if (ImGui::Button("New Mesh", BUTTON_SIZE)) {
            object->add_component(COMP_MESH, new CubeMesh());
            CubeMesh *mesh = (CubeMesh *)object->get_component(COMP_MESH);
            mesh->set_transform(object->get_transform());
        }
    }

    ImGui::Separator();

    // Rigidbody
    if (object->has_component(COMP_RIGIDBODY)) {
        ImGui::Text("Rigidbody");
    }

    // Camera
    if (object->has_component(COMP_CAMERA)) {
        ImGui::Text("Camera");
    }

    // Light
    if (object->has_component(COMP_LIGHT)) {
        Light *light = (Light *)object->get_component(COMP_LIGHT);

        ImGui::Text("Light");

        // Light
        DebugWindow::show_light(light);

        if (ImGui::Button("Delete Light", BUTTON_SIZE)) {
            object->remove_component(COMP_LIGHT);
        }
    }
    else {
        if (ImGui::Button("New Light", BUTTON_SIZE)) {
            object->add_component(COMP_LIGHT, new PointLight());
            PointLight *light = (PointLight *)object->get_component(COMP_LIGHT);
            light->set_position(object->get_transform().position);
        }
    }

    ImGui::Separator();
}

/* show_material
 */
void DebugWindow::show_material(Mesh *mesh) {
    ImGui::PushID("material");

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

    ImGui::Text("Ambient");
    ImGui::SameLine();

    ImGui::PushID("ambient");
    material.ambient = DebugWindow::show_color3(material.ambient);
    ImGui::PopID();

    ImGui::Text("Diffuse");
    ImGui::SameLine();

    ImGui::PushID("diffuse");
    material.diffuse = DebugWindow::show_color3(material.diffuse);
    ImGui::PopID();

    ImGui::Text("Specular");
    ImGui::SameLine();

    ImGui::PushID("specular");
    material.specular = DebugWindow::show_color3(material.specular);
    ImGui::PopID();

    ImGui::Text("Shininess");
    ImGui::SameLine();

    ImGui::PushID("shininess");
    material.shininess = DebugWindow::show_float(material.shininess, 1.0f);
    ImGui::PopID();

    mesh->set_material(material);

    ImGui::PopID();
}

/* show_light
 */
void DebugWindow::show_light(Light *light) {
    ImGui::PushID("light");

    vec3 ambient = light->get_ambient();
    vec3 diffuse = light->get_diffuse();
    vec3 specular = light->get_specular();

    ImGui::Text("Ambient");
    ImGui::SameLine();

    ImGui::PushID("ambient");
    ambient = DebugWindow::show_color3(ambient);
    ImGui::PopID();

    ImGui::Text("Diffuse");
    ImGui::SameLine();

    ImGui::PushID("diffuse");
    diffuse = DebugWindow::show_color3(diffuse);
    ImGui::PopID();

    ImGui::Text("Specular");
    ImGui::SameLine();

    ImGui::PushID("specular");
    specular = DebugWindow::show_color3(specular);
    ImGui::PopID();

    light->set_ambient(ambient);
    light->set_diffuse(diffuse);
    light->set_specular(specular);

    ImGui::PopID();
}

/* show_float
 */
float DebugWindow::show_float(const float value, float step, float min, float max) {
    float new_value = value;
    ImGui::DragScalar("", ImGuiDataType_Float, &new_value, step, &min, &max, "%.2f");
    return new_value;
}

/* show_vec3
 */
vec3 DebugWindow::show_vec3(const vec3 vector, float step, float min, float max) {
    float vector_v4[4] = {vector.x, vector.y, vector.z, 1};
    ImGui::DragFloat3("", vector_v4, step, min, max, "%.2f");
    return vec3(vector_v4[0], vector_v4[1], vector_v4[2]);
}

/* show_color3
 */
vec3 DebugWindow::show_color3(const vec3 color, ImGuiColorEditFlags flags) {
    ImVec4 color_v4 = ImVec4(color.x, color.y, color.z, 1);
    ImGui::ColorEdit3("", (float *)&color_v4, flags);
    return vec3(color_v4.x, color_v4.y, color_v4.z);
}
