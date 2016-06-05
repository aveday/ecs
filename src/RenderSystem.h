#pragma once

#include <GL/glew.h>
#include "EntityManager.h"
#include "Component.h"

class RenderSystem {
public: 
    void run();

private:
    void LoadProgram(Shader&);
    GLuint LoadShader(GLenum type, const char *filename);
};

