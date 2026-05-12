#include "game_play_state.h"

#include "entity_manager.h"
#include "engine_state.h"
#include "camera.h"

#include "add_player.h"
#include "add_tile.h"

void game_play_state_on_enter(void *data)
{
    SDL_Log("[GamePlay On Enter State]");

    EngineState *engine_state = (EngineState *)data;
    EntityManager *entity_manger = &engine_state->entity_manager;

    engine_state->player_ref = add_player(entity_manger);


    add_tile(entity_manger,1,1);
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
    EntityManager *entity_manager = &engine_state->entity_manager;

    Camera2D *camera = &engine_state->camera;

    // before render, every frame
    // start from 1 since zero is nil
    for (int i = 1; i <= entity_manager->count; ++i) {

        Entity *e = entity_manager_get_by_index(entity_manager,i);
        if(!entity_valid(e)) continue;

        // get Texture from entity
        SDL_Texture *tx = engine_state->asset_manager.texture_assets[e->sprite.asset_texture_index].texture;

        // get screen point
        SDL_FPoint screen_point =
        camera_world_to_screen_r(
        // camera_screen_to_world_r(
                    &engine_state->camera,
                    e->pos.x,
                    e->pos.y
                    );

        // SDL_Log("%f %f - %f %f",screen_point.x,screen_point.y,(float)engine_state->window_width, (float)engine_state->window_height);
        // SDL_Log("offset: %f %f | window: %d %d",
        //     engine_state->camera.offset_x,
        //     engine_state->camera.offset_y,
        //     engine_state->window_width,
        //     engine_state->window_height);

        float size_w = camera_world_to_screen_size(&engine_state->camera,1);
        float size_h = camera_world_to_screen_size(&engine_state->camera,1);

        // SDL_Log("offset: %f %f | window: %d %d | screen_point: %f %f",
        //     engine_state->camera.offset_x,
        //     engine_state->camera.offset_y,
        //     engine_state->window_width,
        //     engine_state->window_height,
        //     screen_point.x,
        //     screen_point.y);

        SDL_FRect src = {0,0,16,16};
        SDL_FRect dest = {
            screen_point.x - 0.5f,
            screen_point.y - 0.5f,
            // e->pos.x,
            // e->pos.y,
            size_w,
            size_h
        };

        // render texture
        SDL_RenderTextureRotated(engine_state->renderer,tx,&src,&dest,0,&(SDL_FPoint){0,0},SDL_FLIP_NONE);
    }

    // editor mode
    if(engine_state->edit_menu){

        // float mousex = engine_state.ge;
        // SDL_FRect r = {engine_state->world_tile_mouse.x,engine_state->world_tile_mouse.y,1,1};

        // r.w = 16;
        // r.y = 16;
        // SDL_Log("%f %f",r.x,r.y);

        SDL_FRect r ={engine_state->world_tile_mouse.x,engine_state->world_tile_mouse.y,camera->zoom,camera->zoom};

        SDL_SetRenderDrawColor(engine_state->renderer, 255,100,100,255);
        SDL_RenderRect(engine_state->renderer, &r);
    }
}
