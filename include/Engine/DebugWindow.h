#pragma once

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"


class Engine;
class Object3D;


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
        static void show_objects();
        static void show_transform(Object3D *object);

        static Engine *p_engine;
};