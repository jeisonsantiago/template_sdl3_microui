#ifndef GAME_PLAY_STATE_H
#define GAME_PLAY_STATE_H

// void (*on_enter)(void*data);
// void (*on_exit)(void*data);
// void (*update)(float dt, void*data);
// void (*render)(void*data);
// void *instance_data; // state specific

void game_play_state_on_enter(void*data);
void game_play_state_on_exit(void*data);
void game_play_state_update(float dt, void*data);
void game_play_state_render(void*data);
// void *instance_data; // state specific

#endif // GAME_PLAY_STATE_H
