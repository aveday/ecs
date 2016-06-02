#pragma once
#include <iostream>
#include <stdint.h>
#include <stdlib.h>
#include <vector>
#include <list>
#include "System.h"
#include "Component.h"

#define MAX_ENTS 10000

template <typename T> std::vector<T> component_vector;
template <typename T> uint64_t component_mask;

struct ECS {
    void run();
    int entity_count = 0;
    int component_types = 0;
    bool running = true;
    std::vector<uint64_t> entity_mask = std::vector<uint64_t>(MAX_ENTS);
    std::list<System*> systems;

    ECS(std::list<System*> systems);
    void add_system(System *system);

    inline int new_entity();
    template <typename T> inline void add_component(int entity, T component);
    template <typename T> inline void remove_component(int entity);

};

/* Create a new entity, and return its ID */
int ECS::new_entity()
{
    if(entity_count < MAX_ENTS)
        return entity_count++;
    else
        exit(EXIT_FAILURE);
}

/* Add a new component to an entity */
template <typename T>
void ECS::add_component(int entity, T component)
{
    // if first component type instance -> create maps
    if(!component_mask<T>) {
        component_mask<T> = 1 << component_types++;
        component_vector<T> = std::vector<T>(MAX_ENTS);
    }
    // add component to vector and mark entity bitmask
    component_vector<T>[entity] = T(component);
    entity_mask[entity] |= component_mask<T>;
}

/* Remove a component from an entity */
template <typename T>
void ECS::remove_component(int entity)
{
    if(component_mask<T>)
        entity_mask[entity] &= ~component_mask<T>;
}

#ifdef ECS_IMPLEMENTATION
/* Construct ECS with a list of systems */
ECS::ECS(std::list<System*> systems)
{
    for(auto system : systems)
        add_system(system);
}


/* Add and initialise a new System */
void ECS::add_system(System *system)
{
    systems.push_back(system);
    system->init(*this);
}

/* Run all systems in a loop */
void ECS::run()
{
    while (running) {
        for (auto *system : systems) {
            system->step(*this, 1);
        }
    }
}

#endif //ECS_IMPLEMENTATION
