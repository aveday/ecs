#pragma once

#include <GLFW/glfw3.h>

struct WindowComponent {
    const char* title;
    int width = 640;
    int height = 480;
    bool fullscreen = false;
    bool resizable = false;
    GLFWwindow* gl_window = nullptr;
};
