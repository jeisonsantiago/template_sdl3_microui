#include "system_render_entities.h"

static EntityRef render_ref_vector[RENDER_LAYER_COUNT][MAX_ENTITIES];
static int render_ref_vector_count[RENDER_LAYER_COUNT] = {0};

void system_render_entities(EngineState *engine_state){

    // reset render vector counter


    EntityManager *entity_manager = &engine_state->entity_manager;
    Camera2D *camera = &engine_state->camera;

    // clear render_ref_vector_count
    memset(&render_ref_vector_count,0,sizeof(render_ref_vector_count));

    // go over entities and put in the specfici pool layer
    for (int i = 0; i < entity_manager->highest_idx; ++i) {

        EntityRef ref = entity_manager_get_ref(entity_manager,i);
        Entity *e = entity_manager_get_by_index(entity_manager,i);

        if(!engine_state->entity_manager.used[i]) continue;

        // if(!entity_valid(e) || !entity_ref_valid(ref)) continue;

        render_ref_vector[e->sprite.render_layer][render_ref_vector_count[e->sprite.render_layer]++] = ref;
    }

    for (int l = 0; l < RENDER_LAYER_COUNT; ++l) {
        int entity_layer_count = render_ref_vector_count[l];
        for (int i = 0; i < entity_layer_count; ++i) {
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


}

void system_render_entities_test(EngineState *engine_state){

    // clear render_ref_vector_count
    // memset(&render_ref_vector_count,0,sizeof(render_ref_vector_count));

    EntityManager *entity_manager = &engine_state->entity_manager;
    Camera2D *camera = &engine_state->camera;

    // go over entities and put in the specfici pool layer
    for (int i = 0; i < entity_manager->highest_idx; ++i) {
        Entity *e = entity_manager_get_by_index(entity_manager,i);

        if(!engine_state->entity_manager.used[i]) continue;

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
