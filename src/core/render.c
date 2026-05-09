#include "render.h"


void render(EngineState *state)
{
    // set background collor
    SDL_SetRenderDrawColor(state->renderer,30,30,30,SDL_ALPHA_OPAQUE);

    // clear screen with the set color
    SDL_RenderClear(state->renderer);

    /// ----------------------------------------------------
    ///     DRAW CALLS GOES HERE
    /// ----------------------------------------------------



    /// ----------------------------------------------------

    // Swap the back buffer to the front
    SDL_RenderPresent(state->renderer);
}
