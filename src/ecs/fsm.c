#include "fsm.h"

static bool fsm_config_is_valid(const fsm_t *fsm){
    return (fsm != NULL)&&
            (fsm->table != NULL) &&
            (fsm->table_len > 0u);
}

static const fsm_transition_t *find_transition(const fsm_t *fsm, fsm_event_t event){
    for (Uint32 i = 0; i < fsm->table_len; ++i) {
        const fsm_transition_t *transition = &fsm->table[i];

        if((transition->state == fsm->state) && transition->event == event){
            return transition;
        }
    }

    return NULL;
}

fsm_status_t fsm_init(fsm_t *fsm,
                      void *ctx,
                      fsm_state_t initial_state,
                      const fsm_transition_t *table,
                      uint32_t table_len,
                      fsm_action_t on_entry,
                      fsm_action_t on_exit)
{
    if ((fsm == NULL) || (table == NULL) || (table_len == 0u))
    {
        return FSM_INVALID;
    }

    fsm->ctx = ctx;
    fsm->state = initial_state;
    fsm->table = table;
    fsm->table_len = table_len;
    fsm->on_entry = on_entry;
    fsm->on_exit = on_exit;

    return FSM_OK;
}

fsm_state_t fsm_get_state(const fsm_t *fsm)
{
    if (!fsm_config_is_valid(fsm))
    {
        return 0u;
    }

    return fsm->state;
}

fsm_status_t fsm_dispatch(fsm_t *fsm, fsm_event_t event, const void *data)
{
    const fsm_transition_t *transition;

    if (!fsm_config_is_valid(fsm))
    {
        return FSM_INVALID;
    }

    transition = find_transition(fsm, event);

    if (transition == NULL)
    {
        return FSM_NO_TRANSITION;
    }

    /* State change? */
    if (transition->next_state != fsm->state)
    {
        if (fsm->on_exit != NULL)
        {
            fsm->on_exit(fsm->ctx, event, data);
        }

        fsm->state = transition->next_state;

        if (fsm->on_entry != NULL)
        {
            fsm->on_entry(fsm->ctx, event, data);
        }
    }

    /* Transition action */
    if (transition->action != NULL)
    {
        transition->action(fsm->ctx, event, data);
    }

    return FSM_OK;
}
