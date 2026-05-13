#ifndef PROCESS_INPUT_H
#define PROCESS_INPUT_H


#include "input_state.h"
#include "engine_state.h"

void input_init_defaults(InputMapper *input_mapper);
void input_update_state(InputState *input_state, InputMapper *input_mapper, const bool *raw_keyboard);

void process_input(SDL_Event *event, EngineState *state);
void update_block_position(EngineState *state);

#endif // PROCESS_INPUT_H
