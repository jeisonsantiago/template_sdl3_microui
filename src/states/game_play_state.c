#include "game_play_state.h"

#include "entity_manager.h"
#include "engine_state.h"
#include "camera.h"

#include "add_player.h"
#include "editor.h"

#include "process_input.h"
// #include "editor.h"
#include "system_render_entities.h"

void game_play_state_on_enter(void *data)
{
    SDL_Log("[GamePlay On Enter State]");

    EngineState *engine_state = (EngineState *)data;
    EntityManager *entity_manger = &engine_state->entity_manager;

    engine_state->player_ref = add_player(entity_manger);

    // add_tile(entity_manger,1,1);
    // add_tile(entity_manger,2,1);
    // add_tile(entity_manger,3,1);
    // add_tile(entity_manger,4,1);
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

    camera_update_smooth_follow(&engine_state->camera,player->pos.x, player->pos.y,0.12f);
    // engine_state->camera.x = player->pos.x;
    // engine_state->camera.y = player->pos.y;
    if(engine_state->input_state.active_actions[ACTION_MOVE_UP]){
        player->pos.y -= 2 * dt;
    }
    if(engine_state->input_state.active_actions[ACTION_MOVE_DOWN]){
        player->pos.y += 2 * dt;
    }
    if(engine_state->input_state.active_actions[ACTION_MOVE_LEFT]){
        player->pos.x -= 2 * dt;
    }
    if(engine_state->input_state.active_actions[ACTION_MOVE_RIGHT]){
        player->pos.x += 2 * dt;
    }
}

void game_play_state_render(void *data)
{
    EngineState *engine_state = (EngineState *)data;


    system_render_entities(engine_state);

    // editor render
    editor_render(engine_state);

}
