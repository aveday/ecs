#include <stdio.h>
#include <stdint.h>
#include <vector>
#include <typeinfo>
#include <typeindex>
#include <unordered_map>
#define MAX_ENTS 10000

typedef struct { int a, b; } Component_A;
typedef struct { int c, d; } Component_B;

std::unordered_map<std::type_index, void*> component_vectors; 
std::unordered_map<std::type_index, uint16_t> component_masks;
std::vector<uint64_t> entity_masks(MAX_ENTS);

template <typename T>
inline std::type_index typeid_index(T) {
    return std::type_index(typeid(T));
}

int entity_count = 0;
int new_entity() {
    return entity_count++;
}

template <typename T>
void add_component(int entity, T component) {

    // check if first component type instance, and create maps
    auto type = typeid_index(component);
    if( !component_masks.count(type) ) {
        component_masks[type] = 1 << (component_masks.size() - 1);
        component_vectors[type] = new std::vector<T>(MAX_ENTS);
    }

    (*(std::vector<T>*)component_vectors[type])[entity] = component;
    entity_masks[entity] |= component_masks[type];
}

int main() {

    Component_A a = {1,2};
    Component_B b = {3,4};

    auto e = new_entity();
    add_component(e, a);
    add_component(e, b);
    printf("%d\n",entity_masks[e]);

    return 0;
}
