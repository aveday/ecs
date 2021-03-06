#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "glm.h"

typedef glm::mat4 Transform;

struct Window {
    const char* title;
    int width = 640;
    int height = 480;
    bool fullscreen = false;
    bool resizable = false;
    GLFWwindow* gl_window = nullptr;
};

struct Clock {
    float min;
    float start_time = (float)glfwGetTime(); //FIXME
    float time = 0;
    float dt = 0;
};

struct Camera {
    float fov = 45;
    float aspect = 4.0/3.0f; //FIXME
    float near = 0.1f;
    float far = 1000.0f;
    mat4 projection = mat4();
    mat4 modelMatrix = mat4();
    mat4 cameraMatrix = mat4();
    vec3 position = vec3();
};

struct Model {
    const char* vs;
    const char* fs;
    void (*gen)(Model&);
    mat4 transform = mat4();

    vec3 color = vec3(1);
    GLuint program = 0;
    GLuint vao = 0;
    GLuint vbo = 0;
    int num_vertices = 0;
};

