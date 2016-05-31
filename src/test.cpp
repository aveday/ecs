#include <stdio.h>
#include "ecs.h"

typedef struct { int a, b; } Component_A;
typedef struct { int c, d; } Component_B;

int main()
{
    auto e = new_entity();
    add_component(e, Component_A{1,2});
    add_component(e, Component_B{3,4});

    printf("%d\n", get_component<Component_B>(e).d);

    return 0;
}

