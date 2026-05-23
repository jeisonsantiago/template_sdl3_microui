#include "process_input.h"
// #include "microui_helpers.h"

#include "editor.h"

void update_block_position(EngineState *state){

    float mx, my;
    SDL_GetMouseState(&mx, &my);

    float lx, ly;
    SDL_RenderCoordinatesFromWindow(state->renderer, mx, my, &lx, &ly);

    SDL_FPoint world = camera_screen_to_world_r(&state->camera, lx, ly);

    // snap to grid
    float snapped_x = SDL_floorf(world.x);
    float snapped_y = SDL_floorf(world.y);

    state->world_tile_mouse.x = (int)snapped_x;
    state->world_tile_mouse.y = (int)snapped_y;

    SDL_FPoint screen = camera_world_to_screen_r(&state->camera, snapped_x, snapped_y);

    state->screen_tile_mouse.x= screen.x;
    state->screen_tile_mouse.y= screen.y;
}

void process_input(SDL_Event *event, EngineState *state)
{
    // pool the operating system for events
    // update_block_position(state);


    if(state->editor.is_editor){
        editor_events(event,state);
    }

    switch (event->type) {
    case SDL_EVENT_QUIT:
        state->is_running = false;
        break;
    case SDL_EVENT_KEY_DOWN: {
        if (event->key.repeat) break; // ignore held repeats
        if (event->key.scancode == SDL_SCANCODE_F10) {
            state->editor.is_editor = !state->editor.is_editor;
        }
        break;
    }
    case SDL_EVENT_MOUSE_MOTION:{
        // block position
        // Vector2 worldPos = GetScreenToWorld2D(GetMousePosition(),gameData.camera);
        // this->gameData.mouseWorldPos = worldPos;
        // this->gameData.mouseBlockPos.x = (int)floor(worldPos.x);
        // this->gameData.mouseBlockPos.y = (int)floor(worldPos.y);

        // state->world_tile_mouse.x = (int)SDL_floorf(event->motion.x) * state->camera.zoom + (state->window_width * 0.5f);
        // state->world_tile_mouse.y = (int)SDL_floorf(event->motion.y) * state->camera.zoom + (state->window_height * 0.5f);

        // SDL_FPoint c = camera_screen_to_world_r(
        //             &state->camera,
        //             event->motion.x,
        //             event->motion.y
        //             );
        // state->world_tile_mouse.x = (int)SDL_floorf(c.x) * (state->camera.zoom) + (state->window_width * 0.5f);
        // state->world_tile_mouse.y = (int)SDL_floorf(c.y) * (state->camera.zoom) + (state->window_height * 0.5f);

        // state->world_tile_mouse.x = (int)SDL_floorf(c.x) * (state->camera.zoom) + state->camera.offset_x;
        // state->world_tile_mouse.y = (int)SDL_floorf(c.y) * (state->camera.zoom) + state->camera.offset_y;

        // SDL_Log("%f %f",state->world_tile_mouse.x, state->world_tile_mouse.y);



        break;
    }
    }
    // microui_events(state->ctx,event, state->renderer);
}

void input_init_defaults(InputMapper *input_mapper){
    input_mapper->key_bindins[ACTION_MOVE_UP]       = SDL_SCANCODE_W;
    input_mapper->key_bindins[ACTION_MOVE_DOWN]     = SDL_SCANCODE_S;
    input_mapper->key_bindins[ACTION_MOVE_LEFT]     = SDL_SCANCODE_A;
    input_mapper->key_bindins[ACTION_MOVE_RIGHT]    = SDL_SCANCODE_D;
    input_mapper->key_bindins[ACTION_FIRE_WEAPON]   = SDL_SCANCODE_SPACE;
    input_mapper->key_bindins[ACTION_USE]           = SDL_SCANCODE_E;
}

void input_update_state(InputState *input_state, InputMapper *input_mapper, const bool *raw_keyboard)
{
    // loop over actions
    for (int i = 0; i < ACTION_COUNT; ++i) {
        // look over the key related to this index
        SDL_Scancode bound_key = input_mapper->key_bindins[i];

        // SDL_Log("raw: %i",raw_keyboard[i]);
        // if key is held down set actopm
        input_state->active_actions[i] = raw_keyboard[bound_key];
    }
}
