#include <stdio.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define ECS_IMPLEMENTATION
#include "ecs.h"

#include "Component.h"
#include "System.h"
#include "WindowSystem.h"

#define FPS_CAP 60

int main()
{
    // Create Entity-Component System and game entity
    ECS ecs({ new WindowSystem });
    auto player = ecs.new_entity();

    // Create a new game window
    ecs.add_global_component( Window{"ECStest"} );
    ecs.add_global_component( Clock{1.0/FPS_CAP} );
            
    // Print debug info
    printf("%d\n", component_vector<Window>[0].width);

    // Run ECS
    ecs.run();

    return 0;
}
