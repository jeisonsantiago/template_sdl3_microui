#include "system_cooldown.h"

void system_cooldown(EngineState *engine_state, float dt){
    EntityManager *entity_manager = &engine_state->entity_manager;

    // go over entities and put in the specfici pool layer
    for (int i = 0; i < entity_manager->highest_idx; ++i) {


        // Entity *e = entity_manager_get_by_index(entity_manager,i);

        for (int s = 0; s < STATE_COUNT; ++s) {
            EntityTimer *e_timer = &entity_manager->timers[i][s];

            if(e_timer->ready) continue;

            e_timer->elapsed += dt;
            // SDL_Log("elapsed:%f",e_timer->elapsed);
            if(e_timer->elapsed >= e_timer->duration){
                e_timer->elapsed = 0.0f;
                e_timer->ready = true;
            }
        }
    }

}