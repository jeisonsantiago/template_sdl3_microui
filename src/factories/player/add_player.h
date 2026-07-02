#ifndef ADD_PLAYER_H
#define ADD_PLAYER_H

#include "entity_manager.h"
#include "core_definitions.h"

#include "fsm.h"

enum
{
    ST_IDLE     = 0,
    ST_MOVE     = 1,
    ST_ATTACK   = 2
};

enum
{
    EV_IDLE     = 1,
    EV_MOVE     = 2,
    EV_ATTACK   = 3
};

/* Test context: track which callbacks ran and what happened */
typedef struct
{
    int entry_calls;
    int exit_calls;
    int action_calls;
    int call_order[8];
    int call_index;
    fsm_event_t last_event;
} fsm_test_ctx_t;



EntityRef add_player(EntityManager *entity_manager, float x, float y, MapLayer map_layer);
#endif // ADD_PLAYER_H
