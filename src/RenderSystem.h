#pragma once

#include "ecs.h"
#include "Component.h"

class RenderSystem : public System {
public: 
    void process(int e);
    inline bitmask mask() {
        return ECS::mask<Window>();
    }

};

