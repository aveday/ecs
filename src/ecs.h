#pragma once
#include <stdint.h>
#include <stdlib.h>
#include <vector>
#include <list>
#include "System.h"

#define MAX_ENTS 10000

template <typename T> std::vector<T> component_vector;
template <typename T> uint64_t component_mask;

struct ECS {
    int entity_count;
    int component_types;
    bool running = true;

    std::vector<uint64_t> entity_mask = std::vector<uint64_t>(MAX_ENTS);

    std::list<System*> systems;

    void init();
    void run(int dt);

    int new_entity();
    void add_system(System *system);
    template <typename T> T& get_component(int entity);
    template <typename T> void add_component(int entity, T component);
    template <typename T> void remove_component(int entity);
};

#ifdef ECS_IMPLEMENTATION
/* Create a new entity, and return its ID */
int ECS::new_entity()
{
    if(entity_count < MAX_ENTS)
        return entity_count++;
    else
        exit(EXIT_FAILURE);
}

/* Get a reference to a component on an entity */
template <typename T>
T& ECS::get_component(int entity)
{
    return component_vector<T>[entity];
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
    component_vector<T>[entity] = component;
    entity_mask[entity] |= component_mask<T>;
}

/* Remove a component from an entity */
template <typename T>
void ECS::remove_component(int entity)
{
    if(component_mask<T>)
        entity_mask[entity] &= ~component_mask<T>;
}

void ECS::add_system(System *system)
{
    systems.push_back(system);
}

void ECS::init()
{
    for(System *system : systems) {
        system->init(*this);
    }
}

void ECS::run(int dt)
{
    while (running) {
        for (auto *system : systems) {
            system->run(*this, dt);
        }
    }
}

#endif //ECS_IMPLEMENTATION
