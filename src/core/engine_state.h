#ifndef ENGINE_STATE_H
#define ENGINE_STATE_H

#include "asset_manager.h"
// #include "staste
#include "../states/game_state.h"
#include "../ecs/entity_manager.h"
#include "camera.h"
#include "input_state.h"

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
}EngineState;

void engine_state_init(EngineState *self);

#endif // ENGINE_STATE_H
