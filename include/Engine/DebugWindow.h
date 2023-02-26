#pragma once

// Includes
#include "Engine/utils/types.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"


class Engine;
class Object3D;
class Mesh;
class Light;


class DebugWindow {
    public:
        static void init(Engine *engine);
        static void close();

        static void create_window();
        static void render();
        static void render_draw_data();

        static void add_mouse_button_event(int button, int action);

        static bool want_capture_mouse();

    private:
        static void show_window(bool *open);

        static void show_lighting();
        static void show_light(Light *light);

        static void show_objects();
        static void show_transform(Object3D *object);
        static void show_components(Object3D *object);
        static void show_material(Mesh *mesh);

        static float show_float(const float value, float step = 0.01f, float min = NULL, float max = NULL);
        static vec3 show_vec3(const vec3 vector, float step = 0.01f, float min = NULL, float max = NULL);
        static vec3 show_color3(const vec3 color, ImGuiColorEditFlags flags = 0);

        static Engine *p_engine;
};