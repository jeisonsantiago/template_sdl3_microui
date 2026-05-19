#include "editor.h"

EntityRef editor_add_tile(EngineState *engine_state, float x, float y, int asset_index, int texture_index)
{

    EntityRef ref = entity_manager_add(&engine_state->entity_manager,KIND_TILE);
    Entity *e = entity_manager_get(&engine_state->entity_manager,ref);

    e->pos = (SDL_FPoint){x,y};

    e->sprite.asset_texture_index = asset_index;
    e->sprite.texture_index = texture_index;

    map_set(&engine_state->world_map,x,y,engine_state->selected_layer,ref);

    return ref;
}

void editor_on_click_create_tile(EngineState *engine_state)
{
    SDL_Point block_position = engine_state->world_tile_mouse;

    if(!map_is_inside(&engine_state->world_map,block_position.x, block_position.y)) {
        SDL_Log("Point is outside map boundaries (%i %i).",block_position.x, block_position.y);
        return;
    }

    int selected_tile = engine_state->selected_tile;
    // engine_state->selected_layer = (engine_state->selected_layer != 0)?engine_state->selected_layer:0;
    engine_state->selected_layer = 0;

    // now check if there's something already in the block, if so delete it
    EntityRef block_ref = map_get(&engine_state->world_map,block_position.x, block_position.y,engine_state->selected_layer);


    if(entity_ref_valid(block_ref)){

        // entity_manager_remove(&engine_state->entity_manager,block_ref);
        engine_state_queue_free_add(engine_state,block_ref);

        map_clear(&engine_state->world_map,block_position.x, block_position.y, engine_state->selected_layer);
        // SDL_Log("EXISTS BLOCK:%i %i", block_position.x,block_position.y);
    }

    // if we are creating a tile it will set the world map
    EntityRef created_ref = editor_add_tile(engine_state,block_position.x, block_position.y, 0 , selected_tile);

    // map_set(&engine_state->world_map,block_position.x, block_position.y, engine_state->selected_layer,created_ref);


    SDL_Log("create: %i %i %u %u",block_position.x, block_position.y, created_ref.gen,created_ref.idx);
}

void editor_on_click_delete_tile(EngineState *engine_state)
{
    SDL_Point block_position = engine_state->world_tile_mouse;

    if(!map_is_inside(&engine_state->world_map,block_position.x, block_position.y)) {
        SDL_Log("Point is outside map boundaries (%i %i).",block_position.x, block_position.y);
        return;
    }

    int selected_tile = engine_state->selected_tile;
    // engine_state->selected_layer = (engine_state->selected_layer != 0)?engine_state->selected_layer:0;
    engine_state->selected_layer = 0;

    // now check if there's something already in the block, if so delete it
    EntityRef block_ref = map_get(&engine_state->world_map,block_position.x, block_position.y,engine_state->selected_layer);

    if(entity_ref_valid(block_ref)){
        SDL_Log("EXISTS BLOCK:%i %i", block_position.x,block_position.y);
        map_clear(&engine_state->world_map,block_position.x, block_position.y, engine_state->selected_layer);

        // entity_manager_remove(&engine_state->entity_manager,block_ref);
        engine_state_queue_free_add(engine_state,block_ref);

        SDL_Log("delete: x:%i y:%i",block_position.x, block_position.y);
        return;
    }

    SDL_Log("nothing to delete at: %i %i ",block_position.x, block_position.y);
}

void editor_events(SDL_Event *event, EngineState *engine_state)
{
    if(!engine_state->edit_menu) return;

    switch (event->type) {
    case SDL_EVENT_MOUSE_BUTTON_DOWN:{
        if(event->button.button == SDL_BUTTON_LEFT){ // create tile
            editor_on_click_create_tile(engine_state);
            break;
        }
        if(event->button.button == SDL_BUTTON_RIGHT){ // delete tile
            editor_on_click_delete_tile(engine_state);
            break;
        }

    }
    }
}

void editor_render(EngineState *engine_state)
{
    Camera2D *camera = &engine_state->camera;

    if(engine_state->edit_menu){

        SDL_FRect r ={engine_state->screen_tile_mouse.x,engine_state->screen_tile_mouse.y,camera->zoom,camera->zoom};

        SDL_SetRenderDrawColor(engine_state->renderer, 255,100,100,255);
        SDL_RenderRect(engine_state->renderer, &r);

        // render world map boundaries
        SDL_FPoint top_left = camera_world_to_screen_r(&engine_state->camera,0,0);
        r.x = top_left.x;
        r.y = top_left.y;
        r.w = engine_state->world_map.cols * engine_state->camera.zoom;
        r.h = engine_state->world_map.rows * engine_state->camera.zoom;

        SDL_SetRenderDrawColor(engine_state->renderer, 0,255,0,255);
        SDL_RenderRect(engine_state->renderer, &r);
    }
}


