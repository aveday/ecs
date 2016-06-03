#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "ecs.h"
#include "Component.h"

class WindowSystem : public System
{
public:
    WindowSystem();
    void process(int e);
    uint64_t get_mask() {
        return component_mask<Window>
             | component_mask<Clock>;
    }

private:
    void clear();
    void makeWindow(Window &window);
    bool hasResized(Window &window);
    static void keyPress(
            GLFWwindow* gl_window,
            int key, int scancode, int action, int mods);
};

