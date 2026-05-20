#ifndef ENGINE_STATE_H
#define ENGINE_STATE_H

#include "asset_manager.h"
// #include "staste
#include "../states/game_state.h"
#include "../ecs/entity_manager.h"
#include "camera.h"
#include "input_state.h"
// #include "microui_definitions.h"
#include "map.h"

#include "nuklear.h"


#define MAX_PENDING_IMAGES 1000

typedef struct {
    bool is_running;
    bool has_focus;
    SDL_Window *window;
    SDL_Renderer *renderer;
    int window_width;
    int window_height;
    bool is_paused;

    uint64_t previous_time;

    EntityRef player_ref;

    // game state
    GameState gameplay;
    GameState menu;
    GameState active_state;

    // assets and entities
    AssetManager asset_manager;
    EntityManager entity_manager;

    EntityRef entities_queue_free[MAX_ENTITIES];
    int entities_queue_free_count;

    // camera
    Camera2D camera;

    // inputs ---------------------------------------
    InputState input_state;
    InputMapper input_mapper;

    // world mouse ----------------------------------
    SDL_FPoint world_mouse;
    SDL_FPoint screen_tile_mouse;
    SDL_Point world_tile_mouse;

    // world map
    Map world_map;
    char save_map_filename[200];

    // microui --------------------------------------
    // mu_Context *ctx;
    bool edit_menu;
    int map_layers[3];
    int selected_layer;
    int selected_tile;

    // nuklear
    struct nk_context *nk_ctx;
    struct nk_colorf bg;
    enum nk_anti_aliasing AA;

    // PendingImage pending_images[MAX_PENDING_IMAGES];
    // int pending_images_count;

}EngineState;

void engine_state_init(EngineState *self);

void engine_state_queue_free_add(EngineState *self, EntityRef ref);

// void engine_state_pending_images_add(EngineState *engine_state, PendingImage pending_image);

#endif // ENGINE_STATE_H
