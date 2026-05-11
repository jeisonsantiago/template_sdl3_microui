#ifndef MICROUI_HELPERS_H
#define MICROUI_HELPERS_H

#include "atlas.inl"
#include "asset_manager.h"
#include "engine_state.h"

static const char button_map[256] = {
  [ SDL_BUTTON_LEFT   & 0xff ] =  MU_MOUSE_LEFT,
  [ SDL_BUTTON_RIGHT  & 0xff ] =  MU_MOUSE_RIGHT,
  [ SDL_BUTTON_MIDDLE & 0xff ] =  MU_MOUSE_MIDDLE,
};

static const char key_map[256] = {
  [ SDLK_LSHIFT       & 0xff ] = MU_KEY_SHIFT,
  [ SDLK_RSHIFT       & 0xff ] = MU_KEY_SHIFT,
  [ SDLK_LCTRL        & 0xff ] = MU_KEY_CTRL,
  [ SDLK_RCTRL        & 0xff ] = MU_KEY_CTRL,
  [ SDLK_LALT         & 0xff ] = MU_KEY_ALT,
  [ SDLK_RALT         & 0xff ] = MU_KEY_ALT,
  [ SDLK_RETURN       & 0xff ] = MU_KEY_RETURN,
  [ SDLK_BACKSPACE    & 0xff ] = MU_KEY_BACKSPACE,
};

int text_width(mu_Font font, const char *text, int len);

int text_height(mu_Font font);

// int min(int a, int b);

void window_microui(EngineState *engine_state);

void microui_events(mu_Context *ctx, SDL_Event *event, SDL_Renderer *renderer);



#endif // MICROUI_HELPERS_H
