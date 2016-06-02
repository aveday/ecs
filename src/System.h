#pragma once

struct ECS;

class System {
public:
    virtual void init(ECS &ecs) = 0;
    virtual void run(ECS &ecs, int dt)  = 0;
    uint64_t mask;
};
