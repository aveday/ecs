#include <stdio.h>
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
    printf("%d\n", component_vector<Window>[0].width);

    // Run ECS while the window is open
    ECS::run( component_vector<Window>[game].open );

    return 0;
}
