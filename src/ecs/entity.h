#ifndef ENTITY_H
#define ENTITY_H

#include "components.h"
#include "core_definitions.h"
#include "fsm.h"

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
    AnimationComponent animation;

    EntityRef parent_ref;
    EntityRef first_child_ref;
    EntityRef next_sibling_ref;
    EntityRef previous_sibling_ref;

    // state machine
    fsm_t state_machine;

    // collision related
    void (*on_collion_enter)(uint32_t,uint32_t,void *entity_manager);
    void (*on_collion_stay)(uint32_t,uint32_t,void *entity_manager);
    void (*on_collion_exit)(uint32_t,uint32_t,void *entity_manager);

    // update specfifics
    void (*update_script)(EntityRef,float, void *entity_manager);
}Entity;

bool entity_valid(Entity *self);

#endif // ENTITY_H
