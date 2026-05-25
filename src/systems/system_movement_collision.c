#include "system_movement_collision.h"


void system_update_solids(EngineState *engine_state){
    EntityManager *entity_manager = &engine_state->entity_manager;

    engine_state->solid_entities_count = 0;

    // go over entities and put in the specfici pool layer
    for (int i = 0; i < entity_manager->highest_idx; ++i) {
        Entity *e = entity_manager_get_by_index(entity_manager,i);
        EntityRef ref = entity_manager_get_ref(entity_manager,i);

        if(!engine_state->entity_manager.used[i]) continue;

        if(e->map_layer == MAP_LAYER_SOLID){
            engine_state->solid_entities[engine_state->solid_entities_count++] = ref;
        }
    }

    // SDL_Log("number of solids:%i",engine_state->solid_entities_count);
}

void system_movement_collision_w_solids(EngineState *engine_state)
{
    EntityManager *entity_manager = &engine_state->entity_manager;
    Camera2D *camera = &engine_state->camera;

    // go over entities and put in the specfici pool layer
    for (int i = 0; i < entity_manager->highest_idx; ++i) {
        Entity *e = entity_manager_get_by_index(entity_manager,i);

        if(!engine_state->entity_manager.used[i]) continue;

        if(e->map_layer != MAP_LAYER_ACTORS) continue;

        SDL_FRect e_rect_actor = {
            e->pos.x + e->collider.offset.x,
            e->pos.y + e->collider.offset.y,
            e->collider.width,
            e->collider.height
        };

        for (int s = 0; s < engine_state->solid_entities_count; ++s) {
            EntityRef ref_solid = engine_state->solid_entities[s];
            Entity *e_solid = entity_manager_get(entity_manager,ref_solid);

            // get rectangles
            SDL_FRect e_rect_solid = {
                e_solid->pos.x + e->collider.offset.x,
                e_solid->pos.y + e->collider.offset.y,
                e_solid->collider.width,
                e_solid->collider.height
            };

            // check if there's a collision with actor and solid

        }
    }

}

void system_movement(EngineState *engine_state, float dt)
{
    EntityManager *entity_manager = &engine_state->entity_manager;

    // go over entities and put in the specfici pool layer
    for (int i = 0; i < entity_manager->highest_idx; ++i) {
        Entity *e = entity_manager_get_by_index(entity_manager,i);

        if(!engine_state->entity_manager.used[i]) continue;

        if(e->map_layer != MAP_LAYER_ACTORS) continue;

        // e->physics.acceleration.x += (e->physics.velocity.x * - e->physics.friction) * dt;
        // e->physics.acceleration.y += (e->physics.velocity.y * - e->physics.friction) * dt;
        e->physics.velocity.x += e->physics.acceleration.x * dt;
        e->physics.velocity.y += e->physics.acceleration.y * dt;

        // SDL_Log("acceleration: %f %f",e->physics.velocity.x,e->physics.velocity.y);

        // apply friction

        float damp_factor = SDL_max(0,1-e->physics.friction * dt);
        e->physics.velocity.x *= damp_factor;
        e->physics.velocity.y *= damp_factor;


        // update position
        e->pos.x += e->physics.velocity.x * dt;
        e->pos.y += e->physics.velocity.y * dt;
        // }
    }
}
