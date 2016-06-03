#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "ecs.h"
#include "Component.h"

class WindowSystem : public System {
public:
    WindowSystem();
    void process(int e);
    inline bitmask mask() {
        return ECS::mask<Window, Clock>();
    }

private:
    void clear();
    void makeWindow(Window &window);
    bool hasResized(Window &window);
    static void keyPress(
            GLFWwindow* gl_window,
            int key, int scancode, int action, int mods);
};

