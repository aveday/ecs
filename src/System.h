#pragma once

struct ECS;

class System {
public:
    virtual void init(ECS &ecs) = 0;
    virtual void step(ECS &ecs, int dt)  = 0;
};
