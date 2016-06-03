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
    auto player = ecs.new_entity();

    // Create a new game window
    ecs.add_component(game, Window{ "ECStest"} );
            
    // Print debug info
    printf("%d\n", component_vector<Window>[game].width);

    // Run ECS
    ecs.run();

    return 0;
}

