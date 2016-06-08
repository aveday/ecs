#pragma once

#include <GL/glew.h>
#include "EntityManager.h"
#include "Component.h"

class RenderSystem {
public: 
    void run();
private:
    static const GLuint UNIFORM_CAMERA_MATRIX = 0;
    static const GLuint UNIFORM_CAMERA_POSITION = 2;

    static const GLuint UNIFORM_MODEL = 1;
};

