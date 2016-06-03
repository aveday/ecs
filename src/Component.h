#pragma once

#include <GLFW/glfw3.h>
#include "glm.h"

struct Window {
    const char* title;
    int width = 640;
    int height = 480;
    bool fullscreen = false;
    bool resizable = false;
    bool open = true;
    GLFWwindow* gl_window = nullptr;
};

struct Clock {
    float min;
    float start_time = (float)glfwGetTime();
    float time = 0;
    float dt = 0;
};

struct Camera
{
    float fov = 45;
    float aspect = 16/9.0f; //FIXME
    float near = 0.1f;
    float far = 1000.0f;
    mat4 projection = mat4();
};

