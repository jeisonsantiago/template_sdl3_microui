#ifndef SERIALIZATION_MAP_H
#define SERIALIZATION_MAP_H

#include "engine_state.h"
#include "map.h"

int serialization_save_map(Map *map, EngineState *engine_state, const char* file_name);

#endif // SERIALIZATION_MAP_H
