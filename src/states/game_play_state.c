#include "game_play_state.h"

#include "entity_manager.h"
#include "engine_state.h"
#include "camera.h"

#include "add_player.h"
#include "editor.h"

#include "process_input.h"
// #include "editor.h"
#include "system_render_entities.h"
#include "system_queue_free.h"
#include "system_movement_collision.h"

#include "serialization_map.h"

void game_play_state_on_enter(void *data)
{
    SDL_Log("[GamePlay On Enter State]");

    EngineState *engine_state = (EngineState *)data;
    EntityManager *entity_manger = &engine_state->entity_manager;

    // init world map
    // map_init(&engine_state->world_map,5,5);
    engine_state->player_ref = add_player(entity_manger,1.5f,1.5f, MAP_LAYER_ACTORS);

    // load map
    serialization_load_map(engine_state,"map_01.bin");

    camera_teleport(&engine_state->camera,1,1);

    // reset counters
    engine_state->solid_update_cooldown = 1.0f; // every second
    engine_state->solid_update_count = 0.0f;
}

void game_play_state_on_exit(void *data)
{
    SDL_Log("[GamePlay On Exit State]");
}

void game_play_state_update(float dt, void *data)
{
    EngineState *engine_state = (EngineState *)data;

    EntityManager *entity_manger = &engine_state->entity_manager;

    Entity *player = entity_manager_get_by_index(entity_manger,engine_state->player_ref.idx);

    update_block_position(engine_state);

    // update solids
    engine_state->solid_update_count += dt;
    if(engine_state->solid_update_count > engine_state->solid_update_cooldown){

        system_update_solids(engine_state);

        engine_state->solid_update_count = 0.0f;
    }

    camera_update_smooth_follow(&engine_state->camera,player->pos.x, player->pos.y,0.12f);

    // engine_state->camera.x = player->pos.x;
    // engine_state->camera.y = player->pos.y;

    player->physics.acceleration.x = 0.0f;
    player->physics.acceleration.y = 0.0f;

    if(engine_state->input_state.active_actions[ACTION_MOVE_UP]){
        player->physics.acceleration.y -= player->physics.speed;
    }
    if(engine_state->input_state.active_actions[ACTION_MOVE_DOWN]){
        player->physics.acceleration.y += player->physics.speed;
    }
    if(engine_state->input_state.active_actions[ACTION_MOVE_LEFT]){
        player->physics.acceleration.x -= player->physics.speed;
    }
    if(engine_state->input_state.active_actions[ACTION_MOVE_RIGHT]){
        player->physics.acceleration.x += player->physics.speed;
    }

    // Normalize if non-zero to keep diagonal speed consistent
    const float dx = player->physics.acceleration.x;
    const float dy = player->physics.acceleration.y;
    // const float len2 = dx*dx + dy*dy;
    if (player->physics.acceleration.x != 0.f && player->physics.acceleration.y != 0.f) {
        // player->physics.acceleration *= 0.7071f;
        player->physics.acceleration.x *= 0.7071f;
        player->physics.acceleration.y *= 0.7071f;
    }

    // SDL_Log("acceleration: %f %f",player->physics.acceleration.x,player->physics.acceleration.y);

    // update physics
    // system_movement(engine_state,dt);

    system_movement_collision_w_solids(engine_state,dt);

    // systems
    system_queue_free(engine_state);
}

void game_play_state_render(void *data)
{
    EngineState *engine_state = (EngineState *)data;

    system_render_entities(engine_state);
    // system_render_entities_test(engine_state);

    // debug render
    system_render_entities_debug(engine_state);

    // editor render
    editor_render(engine_state);

}
