#ifndef MICROUI_WIDGETS_H
#define MICROUI_WIDGETS_H

#include "engine_state.h"


int incrementer(mu_Context *ctx, int *value);

int mu_widgets_button(
        mu_Context *ctx,
        EngineState *engine_state,
        SDL_FRect src,
        int w,
        int h,
        int texture_index,
        int bt_index
        );


void mu_widgets_extra_render(EngineState *engine_state);

int mu_extra_image_button(mu_Context *ctx,EngineState *engine_state,SDL_FRect src, int w, int h, SDL_Texture *texture, int bt_index);
int mu_extra_image_rect(mu_Context *ctx, EngineState *engine_state, SDL_FRect src, int w, int h, SDL_Texture *texture, int tile_index);

#endif // MICROUI_WIDGETS_H
