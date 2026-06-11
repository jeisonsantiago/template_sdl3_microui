#include "system_script.h"


void system_script(EngineState *engine_state)
{
    // call update if not null
    EntityManager *entity_manager = &engine_state->entity_manager;

    // go over entities and put in the specfici pool layer
    for (int i = 0; i < entity_manager->highest_idx; ++i) {
        Entity *e = entity_manager_get_by_index(entity_manager,i);
        EntityRef ref = entity_manager_get_ref(entity_manager,i);

        if(e->update_script){
            e->update_script(ref,0,entity_manager);
        }

    }
}
