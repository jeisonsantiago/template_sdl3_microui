#include "system_player_input.h"

#include "fsm.h"
#include "add_player.h"

void system_player_input(EngineState *engine_state)
{

    // get player
    Entity *player = entity_manager_get_by_index(&engine_state->entity_manager,engine_state->player_ref.idx);

    player->physics.acceleration.x = 0.0f;
    player->physics.acceleration.y = 0.0f;

    if(engine_state->input_state.time_out_actions[ACTION_MOVE_UP]){
        player->physics.acceleration.y -= player->physics.speed;
    }
    if(engine_state->input_state.time_out_actions[ACTION_MOVE_DOWN]){
        player->physics.acceleration.y += player->physics.speed;
    }
    if(engine_state->input_state.time_out_actions[ACTION_MOVE_LEFT]){
        player->physics.acceleration.x -= player->physics.speed;
    }
    if(engine_state->input_state.time_out_actions[ACTION_MOVE_RIGHT]){
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

}
