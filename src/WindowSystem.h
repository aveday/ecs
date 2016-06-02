#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "ecs.h"
#include "System.h"
#include "Component.h"

class WindowSystem : public System
{
public:
    void init(ECS &ecs);
    void run(ECS &ecs, int dt);

private:
    void clear();
    void makeWindow(WindowComponent &window);
    bool hasResized(WindowComponent &window);
    static void keyPress(
            GLFWwindow* gl_window,
            int key, int scancode, int action, int mods);
};

