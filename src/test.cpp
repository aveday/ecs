#include <iostream>
#include <GL/glew.h>

#define ECS_IMPLEMENTATION
#define ECS_MAX_ENTS 10000
#include "ecs.h"

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
    auto player = ECS::new_entity( Camera{} );
    auto game = ECS::new_entity(
            Window{"ECStest"},
            Clock{1.0/FPS_CAP});

    // Print debug info
    std::cout << ECS::get_component<Window>(game).width << std::endl;

    // Run ECS while the window is open
    while( ECS::has_components<Window>(game) ) {
        windowing.run();
        rendering.run();
    }

    return 0;
}
