#ifndef EDITOR_H
#define EDITOR_H


#include "engine_state.h"

EntityRef editor_add_tile(EngineState *engine_state, float x, float y, int asset_index, int texture_index, MapLayer map_layer);

void editor_on_click_create_tile(EngineState *engine_state);

void editor_on_click_delete_tile(EngineState *engine_state);

void editor_events(SDL_Event *event, EngineState *engine_state);

void editor_render(EngineState *engine_state);

const char *layer_to_string(MapLayer map_layer);

#endif // EDITOR_H
