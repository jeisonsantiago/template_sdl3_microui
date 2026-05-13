#include "editor.h"

EntityRef editor_add_tile(EngineState *engine_state, float x, float y, int asset_index, int texture_index)
{

    EntityRef ref = entity_manager_add(&engine_state->entity_manager,KIND_TILE);
    Entity *e = entity_manager_get(&engine_state->entity_manager,ref);

    e->pos = (SDL_FPoint){x,y};

    e->sprite.asset_texture_index = asset_index;
    e->sprite.texture_index = texture_index;

    return ref;
}

void editor_on_click(EngineState *engine_state)
{
    SDL_FPoint block_position = engine_state->world_tile_mouse;

    int selected_layer = 0;
    int selected_tile = engine_state->selected_tile;


    // get selected layer
    for (int i = 0; i < 3; ++i) {
         if(engine_state->selected_layer[i] != 0){
             selected_layer = i;
         }
    }

    if(!selected_tile){
        SDL_Log("No Layer was selcted");
    }

    editor_add_tile(engine_state,block_position.x, block_position.y, 0 , selected_tile);
}

void editor_events(SDL_Event *event, EngineState *engine_state)
{
    if(!engine_state->edit_menu) return;

    switch (event->type) {
    case SDL_EVENT_MOUSE_BUTTON_DOWN:{
        SDL_Log("TILE!");
        editor_on_click(engine_state);
        break;
    }
    }
}
