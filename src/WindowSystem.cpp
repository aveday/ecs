#include <iostream>
#include <stdio.h>
#include "WindowSystem.h"

void WindowSystem::init(ECS& ecs)
{
    // initialize GLFW and set window options
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
}

void WindowSystem::keyPress(
        GLFWwindow* gl_window,
        int key, int scancode, int action, int mods)
{
    if(key == GLFW_KEY_ESCAPE)
        glfwSetWindowShouldClose(gl_window, GL_TRUE);

    if(action == GLFW_PRESS) { switch(key) { } }
    else if(action == GLFW_RELEASE) { switch(key) { } }
}

void WindowSystem::makeWindow(WindowComponent &window)
{
    glfwWindowHint(GLFW_RESIZABLE, window.resizable);

    // create the window and set it as current context
    window.gl_window = glfwCreateWindow(
            window.width, window.height, window.title,
            window.fullscreen ? glfwGetPrimaryMonitor() : NULL, NULL);

    glfwMakeContextCurrent(window.gl_window);
    glfwSetKeyCallback(window.gl_window, keyPress);
    glfwSetInputMode(window.gl_window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

    // setup GLEW (must be done after creating GL context)
    glewExperimental = GL_TRUE;
    glewInit();

    // enable depth tests
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
}

void WindowSystem::step(ECS &ecs, int dt)
{
    uint64_t mask = component_mask<WindowComponent>;

    for(int e = 0; e < ecs.entity_count; e++) {
        if( !ecs.check_mask(e, mask) ) continue;

        WindowComponent &window = component_vector<WindowComponent>[e];
        //TODO check resize
        //TODO do entity checking in System::step while looping through subsystems
        if (!window.gl_window)
            makeWindow(window);

        glfwPollEvents();
        clear();
        glfwSwapBuffers(window.gl_window);
    
        if(glfwWindowShouldClose(window.gl_window))
        {

            glfwDestroyWindow(window.gl_window);
            ecs.running = false;
            glfwTerminate();
        }
    }
}

bool WindowSystem::hasResized(WindowComponent &window)
{
    // get size of OpenGL window
    int new_width, new_height;
    glfwGetFramebufferSize(window.gl_window, &new_width, &new_height);
    glViewport(0, 0, new_width, new_height);

    // recalculate projection matrix
    if (new_width  != window.width || new_height != window.height)
    {
        window.height = new_height;
        window.width  = new_width;
        return true;
    }
    return false;
}

void WindowSystem::clear()
{
    // clear screen
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
