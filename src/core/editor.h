#ifndef EDITOR_H
#define EDITOR_H

#include "engine_state.h"

EntityRef editor_add_tile(EngineState *engine_state, float x, float y, int asset_index, int texture_index);


void editor_on_click(EngineState *engine_state);

void editor_events(SDL_Event *event, EngineState *engine_state);

#endif // EDITOR_H
