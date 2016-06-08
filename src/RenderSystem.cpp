#include <iostream>
#include <GL/glew.h>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include "glm.h"
#include "RenderSystem.h"
#include "Mesh.h"
#include "AssetLoader.h"

#define DEBUG 1

void RenderSystem::run()
{
    // set up the camera
    for (int e = 0; e < EM::end(); e++) {
        if (!EM::has_components<Camera>(e))
            continue;

        auto &camera = EM::get_component<Camera>(e);
        printf("setting up camera\n");

        camera.projection = glm::perspective<GLfloat>(45, 4.0f/3.0f, 0.1f, 1000.0f);
        camera.modelMatrix = mat4();

        // update the camera position uniform
        glUniform3fv(UNIFORM_CAMERA_POSITION, 1, glm::value_ptr(camera.position));

        // calculate and set the camera matrix from the view and projection
        camera.cameraMatrix = camera.projection * glm::inverse(camera.modelMatrix);

        glUniformMatrix4fv(UNIFORM_CAMERA_MATRIX, 1, 0, glm::value_ptr(camera.cameraMatrix));
    }

    for (int e = 0; e < EM::end(); e++) {

        if (!EM::has_components<Model>(e) )
            continue;

        auto &model = EM::get_component<Model>(e);

        //FIXME this might not belong here
        if (!model.program)
            model.program = AL::LoadProgram(model.vs, model.fs);
        if (!model.vao)
            model.gen(model);

        // print debug info
        if (DEBUG) {
            printf("Drawing entity %d -- ", e);
            printf("%d vertices -- ", model.num_vertices);
            printf("program %d -- ", model.program);
            const float *pSource = (const float*)glm::value_ptr(model.transform);
            for (int i = 0; i < 16; ++i)
                std::cout << pSource[i] << ", ";
            std::cout << std::endl;
        }

        glUseProgram(model.program);

        // update uniform shader inputs
        glUniformMatrix4fv(UNIFORM_MODEL, 1, 0, glm::value_ptr(model.transform));
        //glUniform3fv(VERTEX_UNIFORM_COLOR, 1, glm::value_ptr(model.color));

        // bind vertex array and draw vertices
        glBindVertexArray(model.vao);
        glDrawArrays(GL_TRIANGLES, 0, model.num_vertices);
        glBindVertexArray(0);
    }
}
