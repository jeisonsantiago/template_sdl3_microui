#ifndef FSM_H
#define FSM_H

// identifiers for states and events
typedef uint16_t fsm_state_t;
typedef uint16_t fsm_event_t;

typedef enum {
    FSM_OK = 0,
    FSM_NO_TRANSITION,
    FSM_INVALID,
}fsm_status_t;


// action callback
typedef void (*fsm_action_t)(void *ctx, fsm_event_t event, const void *data);

// transition rule
typedef struct{
    fsm_state_t state;
    fsm_event_t event;
    fsm_status_t next_state;
    fsm_action_t action;
}fsm_transition_t;

// transition table
typedef struct{
    void *ctx; // user context
    fsm_state_t state; // current state

    const fsm_transition_t *table; // transition table
    uint32_t table_len; // number of table entries

    fsm_action_t on_entry;
    fsm_action_t on_exit;
}fsm_t;

// initialization
fsm_status_t fsm_init(
        fsm_t *fsm,
        void *ctx,
        fsm_state_t initial_state,
        const fsm_transition_t *table,
        uint32_t table_len,
        fsm_action_t on_entry,
        fsm_action_t on_exit
        );

// state query
fsm_state_t fsm_get_state(const fsm_t *fsm);

// dispatch one event
fsm_status_t fsm_dispatch(fsm_t *fsm, fsm_event_t event, const void *data);

#endif // FSM_H

