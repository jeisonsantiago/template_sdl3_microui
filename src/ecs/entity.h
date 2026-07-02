#ifndef ENTITY_H
#define ENTITY_H

#include "components.h"
#include "core_definitions.h"
// #include "fsm.h"
#include "entity_states.h"
#include "input_state.h"
#include "entity_states.h"

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

    bool time_out;
    bool queue_free;
    MapLayer map_layer;

    // components
    PhysicsComponent physics;
    ColliderComponent collider;
    SpriteComponent sprite;
    HealthComponent health;
    AttackComponent attack;
    AnimatorComponent animation;

    EntityRef parent_ref;
    EntityRef first_child_ref;
    EntityRef next_sibling_ref;
    EntityRef previous_sibling_ref;

    // state machine
    EntityState state;



    // cooldowns (reference to an state)
    // Cooldown cooldown_states[STATE_COUNT];
    // Cooldown cooldown_actions[ACTION_COUNT];

    // collision related
    void (*on_collion_enter)(uint32_t,uint32_t,void *entity_manager);
    void (*on_collion_stay)(uint32_t,uint32_t,void *entity_manager);
    void (*on_collion_exit)(uint32_t,uint32_t,void *entity_manager);

    // update specfifics
    void (*update_script)(EntityRef entity_ref,float dt, void *engine_state);
}Entity;

bool entity_valid(Entity *self);
// void entity_register_cooldown_state(Entity *e, int index, float cooldown, bool destroy);
// void entity_register_cooldown_action(Entity *e, int index, float cooldown, bool destroy);

// bool entity_state_cooldown_can_reset(Entity *e, int index);
// bool entity_state_cooldown_time_out(Entity *e, int index);
// void entity_state_cooldown_reset(Entity *e, int index);

#endif // ENTITY_H
