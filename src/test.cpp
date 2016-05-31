#include <stdio.h>
#include "ecs.h"
#include "config.h"
#include "Component.h"

typedef struct { int a, b; } Component_A;
typedef struct { int c, d; } Component_B;

int main()
{
    auto game = new_entity();
    add_component( game, WindowComponent{
            "ECStest", screen_width, screen_height,
            FULLSCREEN, RESIZABLE});

    add_component(game, Component_B{3,4});

    printf("%d\n", get_component<Component_B>(game).d);

    return 0;
}

