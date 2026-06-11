#include "add_player.h"

#include "fsm.h"
#include "helper.h"

static void action_move(void *ctx, fsm_event_t event, const void *data)
{
    SDL_Log("MOVE");
}

static void action_idle(void *ctx, fsm_event_t event, const void *data)
{
    SDL_Log("IDLE");
}

static const fsm_transition_t table[] =
{
    /* MONITORING -> ALERT when threshold is exceeded */
    // { ST_IDLE, EV_IDLE, ST_IDLE, action_idle },
    { ST_IDLE, EV_MOVE, ST_MOVE, action_move },
    { ST_MOVE, EV_IDLE, ST_IDLE, action_idle },

};

void script_update(EntityRef entity_ref, float dt, void *entity_manager){

    EntityManager *e_manager = (EntityManager*)entity_manager;
    Entity *e = entity_manager_get(e_manager,entity_ref);

    if(!e) return;

    // if (helper_vector_lenght(e->physics.velocity) > 0){
    //     fsm_dispatch(&e->state_machine,EV_MOVE,NULL);
    // }else
    if ((int)helper_vector_lenght(e->physics.velocity) == 0){
        fsm_dispatch(&e->state_machine,EV_IDLE,NULL);
    }



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
    e->animation.active = true;

    // set state machine
    // e->state_machine.table = table;
    // e->state_machine.table_len = 2;

    fsm_init(&e->state_machine,e,ST_IDLE,table,2,NULL,NULL);

    // script update
    e->update_script = script_update;

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


