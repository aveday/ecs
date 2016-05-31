#pragma once
#include <stdint.h>
#include <vector>
#include <typeinfo>
#include <typeindex>
#include <unordered_map>
#include "ecs.h"

#define MAX_ENTS 10000
#define GTI(type) std::type_index(typeid(type))

std::unordered_map<std::type_index, void*> component_vectors; 
std::unordered_map<std::type_index, uint16_t> component_masks;
std::vector<uint64_t> entity_masks(MAX_ENTS);

int entity_count = 0;

/* Create a new entity, and return its ID */
int new_entity()
{
    if(entity_count < MAX_ENTS)
        return entity_count++;
    else
        exit(EXIT_FAILURE);
}

/* Get a reference to a component on an entity */
template <typename T>
T& get_component(int entity)
{
    return (*(std::vector<T>*)component_vectors[GTI(T)])[entity];
}

/* Add a new component to an entity */
template <typename T>
void add_component(int entity, T component)
{
    auto type = GTI(T);

    // if first component type instance -> create maps
    if( !component_masks.count(type) ) {
        component_masks[type] = 1 << (component_masks.size() - 1);
        component_vectors[type] = new std::vector<T>(MAX_ENTS);
    }
    // add component to vector and mark entity bitmask
    (*(std::vector<T>*)component_vectors[type])[entity] = component;
    entity_masks[entity] |= component_masks[type];
}

/* Remove a component from an entity */
template <typename T>
void remove_component(int entity)
{
    auto type = GTI(T);
    if( component_masks.count(type) )
        entity_masks[entity] &= ~component_masks[type];
}
