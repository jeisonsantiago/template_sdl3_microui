#ifndef ENGINE_STATE_H
#define ENGINE_STATE_H

#include "asset_manager.h"
// #include "staste
#include "../states/game_state.h"
#include "../ecs/entity_manager.h"
#include "camera.h"
#include "input_state.h"
#include "microui_definitions.h"

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

    // game state
    GameState gameplay;
    GameState menu;

    GameState active_state;

    AssetManager asset_manager;

    EntityManager entity_manager;

    Camera2D camera;

    EntityRef player_ref;

    // inputs
    InputState input_state;
    InputMapper input_mapper;

    // world mouse
    SDL_FPoint world_mouse;

    // microui
    mu_Context *ctx;
    bool edit_menu;
    int selected_layer[3];

    // micro ui variables
    PendingImage pending_images[MAX_PENDING_IMAGES];
    int pending_images_count;

}EngineState;

void engine_state_init(EngineState *self);

void engine_state_pending_images_add(EngineState *engine_state, PendingImage pending_image);

#endif // ENGINE_STATE_H
