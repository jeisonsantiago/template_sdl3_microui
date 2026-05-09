#include "process_input.h"
#include "microui_helpers.h"
#include "camera.h"


void process_input(SDL_Event *event, EngineState *state)
{
    // pool the operating system for events

    switch (event->type) {
    case SDL_EVENT_QUIT:
        state->is_running = false;
        break;
    case SDL_EVENT_MOUSE_MOTION:{
        break;
    }
    }
    microui_events(state->ctx,event, state->renderer);
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
