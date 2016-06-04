#pragma once
#include <stdint.h>
#include <stdlib.h>
#include <vector>
#include <list>

typedef uint64_t bitmask;
const bitmask RESERVED = 0x01;

struct System {
    virtual void process() = 0;
};

class ECS {
private:
    template <typename C>
    static std::vector<C> component_vector;

    template <typename C>
    static bitmask component_mask;

    static const int max_ents;
    static int component_types;
    static std::list<System*> systems;
    static std::vector<bitmask> entity_mask;

public:
    static int end_id; //FIXME privatise

    /* Main API - only use in main program */
    template <typename S, typename... Args>
    static void add_system(Args... args);
    static void run(bool &alive);

    /* System-facing API - must all be inline */
    static inline int new_entity(); 

    template <typename... Cs>
    static inline int new_entity(Cs... c);

    template <typename C>
    static inline void remove_component(int entity);

    template <typename C>
    static inline void add_component(int entity, C c);

    template <typename C, typename... Cs>
    static inline void add_component(int entity, C c, Cs... cs);

    template <typename C>
    static inline C& comp(int e) {
        return component_vector<C>[e];
    }

    template <typename C>
    static inline bool has_component(int e) {
        return !(component_mask<C> & (~entity_mask[e] | RESERVED));
    }

    template <typename C1, typename C2, typename... Cs>
    static inline bool has_component(int e) {
        return has_component<C1>(e) && has_component<C2, Cs...>(e);
    }

};


/* Create a new entity, and return its ID */
int ECS::new_entity()
{
    int e = 0;
    while(entity_mask[e]) e++;
    if(e >= max_ents)
        exit(EXIT_FAILURE);

    entity_mask[e] = RESERVED;
    end_id = (e >= end_id) ? (e + 1) : end_id;
    return e;
}

template <typename... Cs>
int ECS::new_entity(Cs... components) {
    int e = new_entity();
    add_component(e, components...);
    return e;
}

/* Add a new component to an entity */
template <typename C>
void ECS::add_component(int entity, C component)
{
    // create mask and vector on first instance of component type
    if(component_mask<C> == RESERVED) {
        component_mask<C> = 1 << ++component_types;
        component_vector<C> = std::vector<C>(max_ents);
    }
    // add component to vector, mark entity bitmask, unset reserve bit
    component_vector<C>[entity] = C(component);
    entity_mask[entity] |= component_mask<C>;
    entity_mask[entity] &= ~RESERVED;
}

/* Add multiple new components to an entity */
template <typename C, typename... Cs>
void ECS::add_component(int entity, C component, Cs... components) {
        add_component(entity, component);
        add_component(entity, components...);
}

/* Remove a component from an entity */
template <typename C>
void ECS::remove_component(int entity)
{
    if(component_mask<C>)
        entity_mask[entity] &= ~component_mask<C>;
}

#ifdef ECS_IMPLEMENTATION // MAIN API:

#ifndef ECS_MAX_ENTS
#error Must define ECS_MAX_ENTS before ECS implementation
#endif

// component templates
template <typename C> std::vector<C> ECS::component_vector;
template <typename C> bitmask ECS::component_mask = RESERVED;

// static field definitions
const int ECS::max_ents = ECS_MAX_ENTS;
int ECS::component_types = 0;
int ECS::end_id = 0;
std::vector<bitmask> ECS::entity_mask = std::vector<bitmask>(ECS_MAX_ENTS);
std::list<System*> ECS::systems;

/* Add a new System */
template <typename S, typename... Args>
void ECS::add_system(Args... args)
{
    systems.push_back(new S(args...));
}

/* Run all systems in a loop */
void ECS::run(bool &alive)
{
    while (alive)
        for (auto *system : systems)
            system->process();
}

#endif //ECS_IMPLEMENTATION
