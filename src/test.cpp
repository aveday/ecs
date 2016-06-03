#include <stdio.h>
#include <GL/glew.h>

#define ECS_IMPLEMENTATION
#include "ecs.h"

#include "Component.h"
#include "WindowSystem.h"

#define FPS_CAP 60

int main()
{
    // Create Entity-Component System and game entity
    ECS ecs;
    ecs.add_system<WindowSystem>();

    auto game = ecs.new_entity(
            Window{"ECStest"},
            Clock{1.0/FPS_CAP});

    // Print debug info
    printf("%d\n", component_vector<Window>[0].width);

    // Run ECS while the window is open
    ecs.run( component_vector<Window>[game].open );

    return 0;
}
