#include "entity_manager.h"

uint32_t deref(EntityManager *self,EntityRef ref){
    if(ref.idx >= 0 && ref.idx < MAX_ENTITIES && self->used[ref.idx] && ref.gen == self->gen[ref.idx]){
        return ref.idx;
    }

    return INVALID_IDX;
}

uint32_t find_empty(EntityManager *self){
    for (int i = 0; i < MAX_ENTITIES; ++i) {
        if(!self->used[i]){
            return i;
        }
    }

    return INVALID_IDX; // all being used
}

void entity_manager_init(EntityManager *self){
    // self->count = 0;
    // memset(self->entities,0,sizeof(self->entities));
    // memset(self->used,0,sizeof(self->used));
    // memset(self->gen,0,sizeof(self->gen));
    memset(self,0,sizeof(EntityManager));
}

EntityRef entity_manager_add(EntityManager *self, Kind kind)
{
    uint32_t slot = find_empty(self);

    if(slot != INVALID_IDX){
        memset(&self->entities[slot],0,sizeof(Entity));

        // on add
        if (slot + 1 > self->highest_idx) self->highest_idx = slot + 1;

        self->entities[slot].kind = kind;
        self->used[slot] = true;
        self->gen[slot] += 1;
        self->count++;
        return (EntityRef){slot,self->gen[slot]};
    }

    return null_entity();
}

EntityRef entity_manager_get_ref(EntityManager *self,uint32_t idx){

    return (EntityRef){.idx = idx, .gen = self->gen[idx]};
}

Entity *entity_manager_get(EntityManager *self, EntityRef ref){
    uint32_t idx = deref(self,ref);
    return &self->entities[idx];
}

EntityRef null_entity()
{
    return (EntityRef){INVALID_IDX,INVALID_IDX};
}

void entity_manager_remove(EntityManager *self, EntityRef ref)
{
    uint32_t index = deref(self,ref);    
    self->used[index] = false;
    // self->entities[index].pos = (SDL_FPoint){1,1};
    self->count--;
    SDL_Log("REMOVE ENTITY: %i\t count:%i",index,  self->count);
}

void entity_manager_clear(EntityManager *self)
{
    // self->count = 0;

    // memset(self->entities,0,sizeof(self->entities));
    // memset(self->used,0,sizeof(self->used));
    // memset(self->gen,0,sizeof(self->gen));
    entity_manager_init(self);
}

Entity *entity_manager_get_by_index(EntityManager *self, uint32_t idx)
{
    if(idx >= 0 && idx < self->highest_idx){



        return &self->entities[idx];
    }

    return NULL;
}

void entity_manager_set_timer(
        EntityManager *self,
        EntityRef ref,
        EntityState state,
        float duration
        ){

    uint32_t index = deref(self,ref);
    if(index == INVALID_IDX) return;

    EntityTimer *e_timers = &self->timers[index][state];

    e_timers->duration = duration;
    e_timers->elapsed = 0.0f;
    e_timers->ready = true;
}

// void entity_manager_start_timer(
//         EntityManager *self,
//         EntityRef ref,
//         EntityState state
//         ){

//     uint32_t index = deref(self,ref);
//     if(index == INVALID_IDX) return;

//     EntityTimer *e_timers = &self->timers[index][state];
//     e_timers[state].time_out = false;
//     e_timers[state].counter = 0.0f;
// }

// bool entity_manager_timer_out(
//         EntityManager *self,
//         EntityRef ref,
//         EntityState state
//         ){

//     uint32_t index = deref(self,ref);
//     if(index == INVALID_IDX) return false;

//     EntityTimer *e_timers = &self->timers[index][state];

//     return e_timers->time_out;
// }
void entity_manager_init_timer(EntityManager *self, EntityRef ref, EntityState state)
{
    uint32_t index = deref(self,ref);
    if(index == INVALID_IDX) return;

    EntityTimer *e_timers = &self->timers[index][state];
    e_timers->ready = false;
    e_timers->elapsed = 0.0f;
}

bool entity_manager_time_out(
        EntityManager *self,
        EntityRef ref,
        EntityState state
        ){

    uint32_t index = deref(self,ref);
    if(index == INVALID_IDX) return true;

    EntityTimer *e_timers = &self->timers[index][state];
    return e_timers->ready;
}