#include "entity.h"


bool entity_valid(Entity *self)
{
    return (self->kind != KIND_NIL) ;
}

bool entity_ref_valid(EntityRef ref){
    return (ref.idx != INVALID_IDX);
}

EntityRef invalid_entity_ref()
{
    return (EntityRef){INVALID_IDX,INVALID_IDX};
}

// void entity_register_cooldown_state(Entity *e, int index, float cooldown, bool destroy){
//     e->cooldown_states[index].cooldown = cooldown;
//     e->cooldown_states[index].counter = 0.0f;
//     e->cooldown_states[index].destroy = destroy;
//     e->cooldown_states[index].time_out = false;
// }

// void entity_register_cooldown_action(Entity *e, int index, float cooldown, bool destroy){
//     e->cooldown_actions[index].cooldown = cooldown;
//     e->cooldown_actions[index].counter = 0.0f;
//     e->cooldown_actions[index].destroy = destroy;
//     e->cooldown_actions[index].time_out = true;
// }

// bool entity_state_cooldown_time_out(Entity *e, int index){
//     return e->cooldown_states[index].time_out;
// }


// void entity_state_cooldown_reset(Entity *e, int index)
// {
//     e->cooldown_states[index].counter = 0.0f;
//     e->cooldown_states[index].time_out = true;
// }

// bool entity_state_cooldown_can_reset(Entity *e, int index)
// {
//     return e->cooldown_states[index].counter <= 0.0f;
// }
