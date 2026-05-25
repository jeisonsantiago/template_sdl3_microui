#ifndef SYSTEM_MOVEMENT_COLLISION_H
#define SYSTEM_MOVEMENT_COLLISION_H

#include "engine_state.h"


void system_update_solids(EngineState *engine_state);

void system_movement(EngineState *engine_state, float dt);
void system_movement_collision_w_solids(EngineState *engine_state);

#endif // SYSTEM_MOVEMENT_COLLISION_H
