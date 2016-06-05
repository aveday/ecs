#include <iostream>
#include <GL/glew.h>

#define EM_MAX_ENTS 10000
#include "EntityManager.h"

#include "Component.h"
#include "WindowSystem.h"
#include "RenderSystem.h"

#define FPS_CAP 60

int main()
{
    // Create systems
    WindowSystem windowing;
    RenderSystem rendering;

    // Create entities
    auto player = EM::new_entity(
            Camera{},
            Model{},
            Shader{"glsl/specular.vs", "glsl/specular.fs"});

    auto game = EM::new_entity(
            Window{"EMtest"},
            Clock{1.0/FPS_CAP});

    // Print debug info
    std::cout << EM::get_component<Window>(game).width << std::endl;

    // Run systems while the game window exists
    while( EM::has_components<Window>(game) ) {
        windowing.run();
        rendering.run();
    }

    return 0;
}
