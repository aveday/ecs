#pragma once
#include <stdint.h>
#include <stdlib.h>
#include <vector>
#include <list>
#include "Component.h"

#define MAX_ENTS 10000

const uint64_t RESERVED = 0x01;

template <typename T> std::vector<T> component_vector;
template <typename T> uint64_t component_mask = RESERVED;

struct System {
    virtual void init(struct ECS&) = 0;
    virtual void step(struct ECS&) = 0;
};

struct ECS {
    int component_types = 0;
    int end_id = 0;
    bool running = true;
    std::vector<uint64_t> entity_mask = std::vector<uint64_t>(MAX_ENTS);
    std::list<System*> systems;

    /* Main API - only use in main program */
    ECS(std::list<System*> systems);
    void add_system(System* system);
    void run();

    /* System-facing API - must all be inline */
    inline bool check_mask(int entity, uint64_t mask);
    inline int new_entity();

    template <typename T> inline void remove_component(int entity);
    template <typename T> inline void add_component(int entity, T component);
    template <typename T, typename... Ts>
    inline void add_component(int entity, T component, Ts... components);
};

/* Create a new entity, and return its ID */
int ECS::new_entity()
{
    int e = 0;
    while(entity_mask[e]) e++;
    if(e >= MAX_ENTS)
        exit(EXIT_FAILURE);

    entity_mask[e] = RESERVED;
    end_id = (e >= end_id) ? (e + 1) : end_id;
    return e;
}

/* Add a new component to an entity */
template <typename T>
void ECS::add_component(int entity, T component)
{
    // create mask and vector on first instance of component type
    if(component_mask<T> == RESERVED) {
        component_mask<T> = 1 << ++component_types;
        component_vector<T> = std::vector<T>(MAX_ENTS);
    }
    // add component to vector, mark entity bitmask, unset reserve bit
    component_vector<T>[entity] = T(component);
    entity_mask[entity] |= component_mask<T>;
    entity_mask[entity] &= ~RESERVED;
}

/* Add multiple new components to an entity */
template <typename T, typename... Args>
void ECS::add_component(int entity, T component, Args... args) {
        add_component(entity, component);
        add_component(entity, args...);
}

/* Remove a component from an entity */
template <typename T>
void ECS::remove_component(int entity)
{
    if(component_mask<T>)
        entity_mask[entity] &= ~component_mask<T>;
}

// check entity has all mask components and reserve bit isn't set
bool ECS::check_mask(int entity, uint64_t mask)
{
    return !(mask & (~entity_mask[entity] | RESERVED));
}

#ifdef ECS_IMPLEMENTATION // MAIN API:

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
    while (running) for (auto *system : systems)
        system->step(*this);
}

#endif //ECS_IMPLEMENTATION
