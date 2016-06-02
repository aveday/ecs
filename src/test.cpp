#include <stdio.h>
#include <GL/glew.h>

#define ECS_IMPLEMENTATION
#include "ecs.h"

#include "config.h"
#include "Component.h"
#include "System.h"
#include "WindowSystem.h"

int main()
{
    auto ecs = ECS();
    ecs.add_system(new WindowSystem);

    auto game = ecs.new_entity();

    WindowComponent window = { "ECStest",
            screen_width, screen_height,
            FULLSCREEN, RESIZABLE, nullptr };

    ecs.add_component(game, window);

    printf("%d\n", component_vector<WindowComponent>[game].width);

    ecs.init();
    ecs.run(1);


    return 0;
}

