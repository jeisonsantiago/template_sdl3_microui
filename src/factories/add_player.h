#ifndef ADD_PLAYER_H
#define ADD_PLAYER_H

#include "entity_manager.h"
#include "core_definitions.h"

EntityRef add_player(EntityManager *entity_manager, float x, float y, MapLayer map_layer);
#endif // ADD_PLAYER_H
