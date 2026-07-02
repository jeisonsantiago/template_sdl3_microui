#ifndef INPUT_STATE_H
#define INPUT_STATE_H


typedef enum{
    ACTION_UNDEFINED = 0,
    ACTION_MOVE_UP,
    ACTION_MOVE_DOWN,
    ACTION_MOVE_LEFT,
    ACTION_MOVE_RIGHT,
    ACTION_ATTACK,
    ACTION_USE,
    ACTION_COUNT
}GameAction;

typedef struct{
    bool time_out_actions[ACTION_COUNT];
}InputState;

typedef struct{
    SDL_Scancode key_bindins[ACTION_COUNT];
}InputMapper;


#endif // INPUT_STATE_H
