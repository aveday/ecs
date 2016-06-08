#include <cstdio>
#include "Mesh.h"
#include "Component.h"

inline void InitVertexAttrib(GLuint program, const GLchar* attribName,
        int size, int stride, int offset)
{
    GLuint attrib = glGetAttribLocation(program, attribName);
    glVertexAttribPointer(attrib, size, GL_FLOAT, GL_FALSE,
            stride * sizeof(GLfloat), (const void*)(sizeof(GLfloat) * offset));
    glEnableVertexAttribArray(attrib);
}

void CreateBuffers(GLuint &vao, GLuint &vbo)
{
    // create and bind the vertex buffer
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    // create and bind the vertex array
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
}

void Cube(Model &model)
{
    model.num_vertices = 36;

    vec3 positions[]{
        {-0.5, -0.5, -0.5}, {-0.5, -0.5,  0.5},
        {-0.5,  0.5, -0.5}, {-0.5,  0.5,  0.5},
        { 0.5, -0.5, -0.5}, { 0.5, -0.5,  0.5},
        { 0.5,  0.5, -0.5}, { 0.5,  0.5,  0.5}};
    int indices[]{
        0,1,2, 1,3,2,  0,2,6, 0,6,4,  2,3,7, 2,7,6,
        4,6,7, 4,7,5,  1,7,3, 1,5,7,  0,4,1, 1,4,5};
    vec3 normals[]{
        {-1, 0, 0},    { 0, 0,-1},    { 0, 1, 0},
        { 1, 0, 0},    { 0, 0, 1},    { 0,-1, 0}};

    struct {
        vec3 position, normal, color;
    } vertices[model.num_vertices];

    // creat and fill array and buffers
    CreateBuffers(model.vao, model.vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    printf("Generating cube (vbo:%d, vao:%d)\n", model.vbo, model.vao);
    for(int i = 0; i < model.num_vertices; i++)
        vertices[i] = { positions[indices[i]], normals[i/6], vec3(1) };

    //FIXME probably still belongs somewhere else
    // set shader attributes for vertex struct
    InitVertexAttrib(model.program, "Position", 3, 9, 0);
    InitVertexAttrib(model.program, "Normal", 3, 9, 3);
    InitVertexAttrib(model.program, "Color", 3, 9, 6);
    glBindVertexArray(0);
}


void Room(Model &model)
{
    model.num_vertices = 36;

    vec3 positions[]{
        {-0.5, -0.5, -0.5}, {-0.5, -0.5,  0.5},
        {-0.5,  0.5, -0.5}, {-0.5,  0.5,  0.5},
        { 0.5, -0.5, -0.5}, { 0.5, -0.5,  0.5},
        { 0.5,  0.5, -0.5}, { 0.5,  0.5,  0.5}};
    int indices[]{
        1,0,2, 3,1,2,  2,0,6, 6,0,4,  3,2,7, 7,2,6,
        6,4,7, 7,4,5,  7,1,3, 5,1,7,  4,0,1, 4,1,5};
    vec3 normals[]{
        {-1, 0, 0},    { 0, 0,-1},    { 0, 1, 0},
        { 1, 0, 0},    { 0, 0, 1},    { 0,-1, 0}};

    struct {
        vec3 position, normal, color;
    } vertices[model.num_vertices];

    // creat and fill array and buffers
    CreateBuffers(model.vao, model.vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    printf("Generating room (vbo:%d, vao:%d)\n", model.vbo, model.vao);
    for(int i = 0; i < model.num_vertices; i++)
        vertices[i] = { positions[indices[i]], normals[i/6], vec3(1) };

    //FIXME probably still belongs somewhere else
    // set shader attributes for vertex struct
    InitVertexAttrib(model.program, "Position", 3, 9, 0);
    InitVertexAttrib(model.program, "Normal", 3, 9, 3);
    InitVertexAttrib(model.program, "Color", 3, 9, 6);
    glBindVertexArray(0);
}

