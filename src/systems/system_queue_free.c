#include "system_queue_free.h"

void system_queue_free(EngineState *engine_state){
    for (int i = 0; i < engine_state->entities_queue_free_count; ++i) {
        entity_manager_remove(&engine_state->entity_manager,engine_state->entities_queue_free[i]);
        --engine_state->entities_queue_free_count;
    }
}