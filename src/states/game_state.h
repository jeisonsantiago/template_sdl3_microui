#ifndef GAME_STATE_H
#define GAME_STATE_H

typedef struct {
    void (*on_enter)(void*data);
    void (*on_exit)(void*data);
    void (*update)(float dt, void*data);
    void (*render)(void*data);
    void *instance_data; // state specific
}GameState;

void game_state_init(GameState *game_state);

#endif // GAME_STATE_H
