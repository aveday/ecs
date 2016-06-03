#include <iostream>
#include <GL/glew.h>

#define ECS_IMPLEMENTATION
#define ECS_MAX_ENTS 10000
#include "ecs.h"

#include "Component.h"
#include "WindowSystem.h"

#define FPS_CAP 60

int main()
{
    // Create window system
    ECS::add_system<WindowSystem>();

    auto game = ECS::new_entity(
            Window{"ECStest"},
            Clock{1.0/FPS_CAP});

    // Print debug info
    std::cout << ECS::get<Window>(game).width << std::endl;

    // Run ECS while the window is open
    ECS::run( ECS::get<Window>(game).open );

    return 0;
}
