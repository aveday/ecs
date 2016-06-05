#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "EntityManager.h"
#include "Component.h"

class WindowSystem {
public:
    WindowSystem();
    void run();

private:
    void Clear();
    void MakeWindow(Window &window);
    bool HasResized(Window &window);
    static void KeyPress(
            GLFWwindow* gl_window,
            int key, int scancode, int action, int mods);
};

