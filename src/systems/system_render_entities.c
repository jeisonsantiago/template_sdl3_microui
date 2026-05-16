#include "system_render_entities.h"

static EntityRef render_ref_vector[RENDER_LAYER_COUNT][MAX_ENTITIES];
static int render_ref_vector_count[RENDER_LAYER_COUNT] = {0};

void system_render_entities(EngineState *engine_state){

    EntityManager *entity_manager = &engine_state->entity_manager;
    Camera2D *camera = &engine_state->camera;

    // clear render_ref_vector_count
    memset(render_ref_vector_count,0,sizeof(render_ref_vector_count));

    // go over entities and put in the specfici pool layer
    for (int i = 1; i <= entity_manager->count; ++i) {

        EntityRef ref = entity_manager_get_ref(entity_manager,i);
        Entity *e = entity_manager_get_by_index(entity_manager,i);

        if(!entity_valid(e) || !entity_ref_valid(ref)) continue;

        render_ref_vector[e->sprite.render_layer][render_ref_vector_count[e->sprite.render_layer]++] = ref;
    }

    for (int l = 0; l < RENDER_LAYER_COUNT; ++l) {
        int entity_count = render_ref_vector_count[l];
        for (int i = 0; i < entity_count; ++i) {
            EntityRef ref = render_ref_vector[l][i];
            Entity *e = entity_manager_get(entity_manager,ref);

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

            float size_w = camera_world_to_screen_size(&engine_state->camera,1);
            float size_h = camera_world_to_screen_size(&engine_state->camera,1);

            SDL_FRect src = asset_manager_get_texture_rect_by_index(e->sprite.texture_index,&engine_state->asset_manager.texture_assets[e->sprite.asset_texture_index]);
            SDL_FRect dest = {
                screen_point.x - 0.5f,
                screen_point.y - 0.5f,
                size_w,
                size_h
            };

            // render texture
            SDL_RenderTextureRotated(engine_state->renderer,tx,&src,&dest,0,&(SDL_FPoint){0,0},SDL_FLIP_NONE);

        }
    }



    // // before render, every frame
    // // start from 1 since zero is nil
    // for (int i = 1; i <= entity_manager->count; ++i) {

    //     Entity *e = entity_manager_get_by_index(entity_manager,i);
    //     if(!entity_valid(e)) continue;

    //     // get Texture from entity
    //     SDL_Texture *tx = engine_state->asset_manager.texture_assets[e->sprite.asset_texture_index].texture;

    //     // get screen point
    //     SDL_FPoint screen_point =
    //             camera_world_to_screen_r(
    //                 // camera_screen_to_world_r(
    //                 &engine_state->camera,
    //                 e->pos.x,
    //                 e->pos.y
    //                 );

    //     // SDL_Log("%f %f - %f %f",screen_point.x,screen_point.y,(float)engine_state->window_width, (float)engine_state->window_height);
    //     // SDL_Log("offset: %f %f | window: %d %d",
    //     //     engine_state->camera.offset_x,
    //     //     engine_state->camera.offset_y,
    //     //     engine_state->window_width,
    //     //     engine_state->window_height);

    //     float size_w = camera_world_to_screen_size(&engine_state->camera,1);
    //     float size_h = camera_world_to_screen_size(&engine_state->camera,1);

    //     // SDL_Log("offset: %f %f | window: %d %d | screen_point: %f %f",
    //     //     engine_state->camera.offset_x,
    //     //     engine_state->camera.offset_y,
    //     //     engine_state->window_width,
    //     //     engine_state->window_height,
    //     //     screen_point.x,
    //     //     screen_point.y);

    //     SDL_FRect src = asset_manager_get_texture_rect_by_index(e->sprite.texture_index,&engine_state->asset_manager.texture_assets[e->sprite.asset_texture_index]);
    //     SDL_FRect dest = {
    //         screen_point.x - 0.5f,
    //         screen_point.y - 0.5f,
    //         // e->pos.x,
    //         // e->pos.y,
    //         size_w,
    //         size_h
    //     };

    //     // render texture
    //     SDL_RenderTextureRotated(engine_state->renderer,tx,&src,&dest,0,&(SDL_FPoint){0,0},SDL_FLIP_NONE);
    // }
}
