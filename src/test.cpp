#include <iostream>
#include <GL/glew.h>
#include "glm/gtx/transform.hpp"

#define EM_MAX_ENTS 10000
#include "EntityManager.h"

#define AL_MAC_ASSETS 500
#include "AssetLoader.h"

#include "Mesh.h"
#include "Component.h"
//#include "Assets.h"
#include "WindowSystem.h"
#include "RenderSystem.h"

#define FPS_CAP 60

int main()
{
    // Create systems
    WindowSystem windowing;
    RenderSystem rendering;

    mat4 t1 = glm::translate<GLfloat>( vec3( 0, 0,-5) );
    mat4 t2 = glm::translate<GLfloat>( vec3( 0, 0, 5) );
    mat4 t3 = glm::translate<GLfloat>( vec3(-5, 0, 0) );
    mat4 t4 = glm::scale<GLfloat>( vec3(10,10,10) );

    // Create entities
    //EM::new_entity(Model{"glsl/specular.vs", "glsl/specular.fs", &Room, t4});
    auto game = EM::new_entity( Window{"EMtest"}, Clock{1.0/FPS_CAP});
    auto player = EM::new_entity( Camera{} );

    EM::new_entity(Model{"glsl/specular.vs", "glsl/specular.fs", &Cube, t1});
    EM::new_entity(Model{"glsl/specular.vs", "glsl/specular.fs", &Cube, t2});
    EM::new_entity(Model{"glsl/specular.vs", "glsl/specular.fs", &Cube, t3});

    // Print debug info
    std::cout << EM::get_component<Window>(game).width << std::endl;

    // Run systems while the game window exists
    while( EM::has_components<Window>(game) ) {
        windowing.run();
        rendering.run();
        windowing.Display();
    }

    return 0;
}
