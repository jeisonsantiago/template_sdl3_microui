#ifndef ENTITY_H
#define ENTITY_H

#include "components.h"
#include "core_definitions.h"

static const uint32_t INVALID_IDX = -1;

typedef struct {
    uint32_t idx;
    uint32_t gen;
}EntityRef;

bool entity_ref_valid(EntityRef ref);

EntityRef invalid_entity_ref();

typedef struct {
    Kind kind;

    SDL_FPoint pos;
    SDL_FPoint previous_pos;

    bool active;
    bool queue_free;
    MapLayer map_layer;

    // components
    PhysicsComponent physics;
    ColliderComponent collider;
    SpriteComponent sprite;
    HealthComponent health;
    AttackComponent attack;

    EntityRef parent_ref;
    EntityRef first_child_ref;
    EntityRef next_sibling_ref;
    EntityRef previous_sibling_ref;

    // collision related
    // std::function<void(int,int, EntityArray&)> on_collision_enter = nullptr;
    void (*on_collion_enter)(uint32_t,uint32_t,void *entity_manager);
    // std::function<void(int,int, EntityArray&)> on_collision_stay = nullptr;
    void (*on_collion_stay)(uint32_t,uint32_t,void *entity_manager);
    // std::function<void(int,int, EntityArray&)> on_collision_exit = nullptr;
    void (*on_collion_exit)(uint32_t,uint32_t,void *entity_manager);

    // bool has_child(int idx);
}Entity;

bool entity_valid(Entity *self);

#endif // ENTITY_H
