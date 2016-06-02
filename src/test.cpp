#include <stdio.h>
#include <GL/glew.h>

#define ECS_IMPLEMENTATION
#include "ecs.h"

#include "Component.h"
#include "System.h"
#include "WindowSystem.h"

int main()
{
    // Create Entity-Component System and game entity
    ECS ecs({ new WindowSystem });
    auto game = ecs.new_entity();

    // Create a new game window
    ecs.add_component(game, WindowComponent{ "ECStest"} );
            
    // Print debug info
    printf("%d\n", component_vector<WindowComponent>[game].width);

    // Run ECS
    ecs.run();

    return 0;
}

