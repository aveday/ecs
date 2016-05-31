#pragma once

#include <GLFW/glfw3.h>

struct WindowComponent {
    const char* title;
    int width, height;
    bool fullscreen, resizable;
    GLFWwindow* gl_window;
};
