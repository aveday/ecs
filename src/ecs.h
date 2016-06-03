#pragma once
#include <stdint.h>
#include <stdlib.h>
#include <vector>
#include <list>
#include "Component.h"

#define MAX_ENTS 10000

const uint64_t NULL_MASK = 0x01;
const int ECS_ID = 0;

template <typename T> std::vector<T> component_vector;
template <typename T> uint64_t component_mask = NULL_MASK;

struct System {
    virtual void init(struct ECS&) = 0;
    virtual void step(struct ECS&) = 0;
};

struct ECS {
    int component_types = 1;
    int last_id = ECS_ID;
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
    template <typename T> inline void add_component(int entity, T component);
    template <typename T> inline void remove_component(int entity);
    template <typename T> inline void add_global_component(T component)
        { add_component(ECS_ID, component); }
    template <typename T> inline void remove_global_component()
        { remove_component<T>(ECS_ID); }
};

/* Create a new entity, and return its ID */
int ECS::new_entity()
{
    int e = 0;
    while(entity_mask[e]) e++;
    if(e < MAX_ENTS) {
        entity_mask[e] = NULL_MASK;
        last_id = e > last_id ? e : last_id;
        return e;
    } else {
        exit(EXIT_FAILURE);
    }
}

/* Add a new component to an entity */
template <typename T>
void ECS::add_component(int entity, T component)
{
    // create mask and vector on first instance of component type
    if(component_mask<T> == NULL_MASK) {
        component_mask<T> = 1 << component_types++;
        component_vector<T> = std::vector<T>(MAX_ENTS);
    }
    // add component to vector, mark entity bitmask, unset null-mask bit
    component_vector<T>[entity] = T(component);
    entity_mask[entity] |= component_mask<T>;
    entity_mask[entity] &= ~NULL_MASK;
}

/* Remove a component from an entity */
template <typename T>
void ECS::remove_component(int entity)
{
    if(component_mask<T>)
        entity_mask[entity] &= ~component_mask<T>;
}

// check entity has all mask components and null-mask bit isn't set
bool ECS::check_mask(int entity, uint64_t mask)
{
    return !(mask & (~entity_mask[entity] | NULL_MASK));
}

#ifdef ECS_IMPLEMENTATION // MAIN API:

/* Construct ECS with a list of systems */
ECS::ECS(std::list<System*> systems)
{
    entity_mask[ECS_ID] = NULL_MASK;
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
            system->step(*this);
        }
    }
}

#endif //ECS_IMPLEMENTATION
