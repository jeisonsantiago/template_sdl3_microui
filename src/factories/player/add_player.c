#include "add_player.h"

#include "fsm.h"
#include "helper.h"
#include "engine_state.h"


void try_attack(EntityRef entity_ref, EntityManager *entity_manager, EngineState *engine_state){

    if(engine_state->input_state.time_out_actions[ACTION_ATTACK] &&
        !engine_state->previous_input_state.time_out_actions[ACTION_ATTACK]){

        Entity *e = entity_manager_get(entity_manager,entity_ref);

        // if not reached a time out cancel attack
        if(!entity_manager_time_out(entity_manager,entity_ref,STATE_ATTACK)){
            // e->state = STATE_IDLE;
            return;
        }else{
            entity_manager_init_timer(entity_manager, entity_ref,STATE_ATTACK);
            e->state = STATE_ATTACK;
        }
    }
}

void script_update(EntityRef entity_ref, float dt, void *engine){

    EngineState *engine_state = (EngineState*)engine;
    EntityManager *entity_manager = &engine_state->entity_manager;
    Entity *e = entity_manager_get(entity_manager,entity_ref);

    if(!e) return;

    switch (e->state) {
    case STATE_IDLE:{
        if (helper_vector_lenght(e->physics.acceleration) > 0){
            e->state = STATE_WALK;
        }

        //try to attack
        try_attack(entity_ref,entity_manager,engine_state);
        break;
    }
    case STATE_WALK:{
        if ((int)helper_vector_lenght(e->physics.acceleration) == 0){
            e->state = STATE_IDLE;
        }

        //try to attack
        try_attack(entity_ref,entity_manager,engine_state);
        break;
    }
    case STATE_ATTACK:{

        // after attack move to idle
        e->state = STATE_IDLE;
        break;
    }

    }

    // SDL_Log("STATE:%u",e->state);
}

EntityRef add_player(EntityManager *entity_manager, float x, float y, MapLayer map_layer)
{
    EntityRef ref = entity_manager_add(entity_manager,KIND_PLAYER);
    Entity *e = entity_manager_get(entity_manager,ref);

    e->pos = (SDL_FPoint){x,y};
    e->map_layer = map_layer;

    e->collider.width   = 0.5f;
    e->collider.height  = 0.5f;

    // e->collider.width   = 1.0f;
    // e->collider.height  = 1.0f;

    e->collider.offset.x = 0.25f;
    e->collider.offset.y = 0.45f;

    // e->collider.offset.x = 0.0f;
    // e->collider.offset.y = 0.0f;

    e->sprite.asset_texture_index = 2;
    e->sprite.texture_index = 0;
    e->sprite.render_layer = map_layer;

    e->physics.friction = 10.0f;
    e->physics.speed = 20.0f;
    e->physics.acceleration.x = 0;
    e->physics.acceleration.y = 0;
    e->physics.velocity.x = 0;
    e->physics.velocity.y = 0;

    e->animation.base_frame_index = 0;

    // set state machine
    // e->state_machine.table = table;
    // e->state_machine.table_len = 2;

    e->state = STATE_IDLE;
    // fsm_init(&e->state_machine,e,ST_IDLE,table,6,NULL,NULL);

    // script update
    e->update_script = script_update;

    // register cooldown
    // entity_register_cooldown_state(e,STATE_ATTACK,1.0f, false);
    entity_manager_set_timer(entity_manager,ref,STATE_ATTACK,2.0f);

    return ref;
}

// FSM test

/* Optional hooks: run on state change */
static void on_entry(void *ctx, fsm_event_t event, const void *data)
{
    fsm_test_ctx_t *context = (fsm_test_ctx_t*)ctx;
    (void)data;

    context->entry_calls++;
    context->last_event = event;
    context->call_order[context->call_index++] = 2;
}

static void on_exit(void *ctx, fsm_event_t event, const void *data)
{
    fsm_test_ctx_t *context = (fsm_test_ctx_t*)ctx;
    (void)data;

    context->exit_calls++;
    context->last_event = event;
    context->call_order[context->call_index++] = 1;
}

/* Transition action: runs when a transition rule matches */
static void action_record(void *ctx, fsm_event_t event, const void *data)
{
    fsm_test_ctx_t *context = (fsm_test_ctx_t*)ctx;
    (void)data;

    context->action_calls++;
    context->last_event = event;
    context->call_order[context->call_index++] = 3;
}


