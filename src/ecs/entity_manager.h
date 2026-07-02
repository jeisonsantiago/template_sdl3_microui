#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

#include "entity.h"
#include "ecs.h"

typedef struct{
    float duration;
    float elapsed;
    bool ready;
}EntityTimer;

typedef struct{
    Entity          entities[MAX_ENTITIES];
    uint32_t        count;
    uint32_t        highest_idx;

    bool            used[MAX_ENTITIES];
    uint32_t        gen[MAX_ENTITIES];

    // each entity has 10 timers
    EntityTimer timers[MAX_ENTITIES][STATE_COUNT];

}EntityManager;

void entity_manager_init(EntityManager *self);
EntityRef entity_manager_add(EntityManager *self, Kind kind);
EntityRef entity_manager_get_ref(EntityManager *self,uint32_t idx);
Entity *entity_manager_get(EntityManager *self, EntityRef ref);
Entity *entity_manager_get_by_index(EntityManager *self, uint32_t idx);
void entity_manager_remove(EntityManager *self, EntityRef ref);
void entity_manager_clear(EntityManager *self);
EntityRef null_entity();

// timers
void entity_manager_set_timer(
        EntityManager *self,
        EntityRef ref,
        EntityState state,
        float duration
        );

void entity_manager_init_timer(
        EntityManager *self,
        EntityRef ref,
        EntityState state
        );

bool entity_manager_time_out(
        EntityManager *self,
        EntityRef ref,
        EntityState state
        );



// void entity_manager_start_timer(
//         EntityManager *self,
//         EntityRef ref,
//         EntityState state
//         );

// bool entity_manager_timer_out(
//         EntityManager *self,
//         EntityRef ref,
//         EntityState state
//         );


#endif // ENTITY_MANAGER_H
