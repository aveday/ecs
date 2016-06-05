#include <iostream>
#include "RenderSystem.h"

void RenderSystem::run()
{
    for(int e = 0; e < EM::end(); e++) {
        if (!EM::has_components<Model, Shader>(e) )
            continue;

        auto &model  = EM::get_component<Model>(e);
        auto &shader = EM::get_component<Shader>(e);

        if (!shader.program)
            LoadProgram(shader);

    }
}

/* Load and compile a shader given a shader type and filename */
GLuint RenderSystem::LoadShader(GLenum type, const char *filename)
{
    // open the shader source
    FILE *f = fopen(filename, "r");
    if (!f)
    {
        std::cerr << "Unable to open " << filename << " for reading";
        return 0;
    }

    // read the source
    fseek(f, 0, SEEK_END);
    int length = ftell(f);
    fseek(f, 0, SEEK_SET);
    GLchar *source = (char*)malloc(length+1);
    length = fread(source, 1, length, f);
    fclose(f);
    ((char*)source)[length] = '\0';

    // compile the shader
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, (const GLchar**)&source, &length);
    free(source);
    glCompileShader(shader);

    // check the shader
    GLint shader_ok;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &shader_ok);
    if (!shader_ok)
    {
        GLint log_length;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &log_length);
        char *log = (char*)malloc(log_length);
        glGetShaderInfoLog(shader, log_length, NULL, log);
        std::cerr << "Failed to compile " << filename << ".\n" << log;
        free(log);
        glDeleteShader(shader);
        return 0;
    }
    return shader;
}

/* Load the program specified by a shader component */
void RenderSystem::LoadProgram(Shader &shader)
{
    // create shader program, compile and attach vertex and fragment shaders
    GLuint program = glCreateProgram();
    glAttachShader(program, LoadShader(GL_VERTEX_SHADER, shader.vs));
    glAttachShader(program, LoadShader(GL_FRAGMENT_SHADER, shader.fs));

    // link and check the program
    glLinkProgram(program);
    GLint program_ok;
    glGetProgramiv(program, GL_LINK_STATUS, &program_ok);
    if (!program_ok) {
        GLint log_length;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &log_length);
        char *log = (char*)malloc(log_length);
        glGetShaderInfoLog(program, log_length, NULL, log);
        std::cerr << "Error linking the shader program.\n" << log;
        free(log);
        glDeleteProgram(program);
    }

    // validate and set the program value
    glValidateProgram(program);
    shader.program = program;
}
