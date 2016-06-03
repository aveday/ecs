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

struct ECS;

struct System {
    virtual void process(int e) = 0;
    virtual uint64_t get_mask() = 0;
};

struct ECS {
    int component_types = 0;
    int end_id = 0;
    std::vector<uint64_t> entity_mask = std::vector<uint64_t>(MAX_ENTS);
    std::list<System*> systems;

    /* Main API - only use in main program */
    template <typename T, typename... Args>
    void add_system(Args... args);
    void run(bool &alive);

    /* System-facing API - must all be inline */
    inline int new_entity(); 

    template <typename... Ts>
    inline int new_entity(Ts... components);

    template <typename T>
    inline void remove_component(int entity);

    template <typename T>
    inline void add_component(int entity, T component);

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

template <typename... Ts>
int ECS::new_entity(Ts... components) {
    int e = new_entity();
    add_component(e, components...);
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
template <typename T, typename... Ts>
void ECS::add_component(int entity, T component, Ts... components) {
        add_component(entity, component);
        add_component(entity, components...);
}

/* Remove a component from an entity */
template <typename T>
void ECS::remove_component(int entity)
{
    if(component_mask<T>)
        entity_mask[entity] &= ~component_mask<T>;
}

#ifdef ECS_IMPLEMENTATION // MAIN API:

/* Add a new System */
template <typename T, typename... Args>
void ECS::add_system(Args... args)
{
    systems.push_back(new T(args...));
}

/* Run all systems in a loop */
void ECS::run(bool &alive)
{
    while (alive) for (auto *system : systems) {
        // calculate the system mask 
        uint64_t mask = system->get_mask();
        
        // process each entity which fits the system mask
        for(int e = 0; e < end_id; e++)
            if( !(mask & (~entity_mask[e] | RESERVED)) )
                system->process(e);
    }
}

#endif //ECS_IMPLEMENTATION
