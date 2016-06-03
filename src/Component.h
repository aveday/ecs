#pragma once

#include <GLFW/glfw3.h>

struct Window {
    const char* title;
    int width = 640;
    int height = 480;
    bool fullscreen = false;
    bool resizable = false;
    GLFWwindow* gl_window = nullptr;
};

struct Clock
{
    float min;
    float start_time = (float)glfwGetTime();
    float time;
    float dt = 0;
    bool running = false;
};
