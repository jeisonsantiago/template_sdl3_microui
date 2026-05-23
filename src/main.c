#include <stdio.h>

#include "core/engine_state.h"
#include "core/process_input.h"
#include "core/window_events.h"
// #include "microui_helpers.h"

// states
#include "states/game_play_state.h"


#define PHYSICS_FPS 60.0
#define FIXED_TIME_STEP (1.0 / PHYSICS_FPS)

// SDL meaasures time in nanoseconds. 1 second = 1 billion nanoseconds
#define NS_PER_SECOND 1000000000.0

// define target fps
#define TARGET_FPS 144.0
#define TARGET_FPS_TIME_NS (NS_PER_SECOND / TARGET_FPS)

// nuklear
#include "gui_nuklear/nuklear_helpers.h"
#include "nuklear_sdl3_renderer.h"

int main()
{
    // initialize SDL's video subsystem
    if(!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)){
        printf("Failed to initialize SDL: %s\n",SDL_GetError());
    }

    // set engineState
    EngineState *engine_state = (EngineState*)malloc(sizeof(EngineState));
    if(engine_state){
        engine_state_init(engine_state);
    }

    // create window with props

    //uint64_t previous_time = SDL_GetTicksNS();
    engine_state->previous_time = SDL_GetTicksNS();
    double accumulator = 0.0;

    /// set gameplay state
    engine_state->gameplay.on_enter = game_play_state_on_enter;
    engine_state->gameplay.on_exit = game_play_state_on_exit;
    engine_state->gameplay.update = game_play_state_update;
    engine_state->gameplay.render = game_play_state_render;

    // set gameplay to be the active state
    engine_state->active_state = engine_state->gameplay;

    // initialize current active state if set
    if(engine_state->active_state.on_enter){
        engine_state->active_state.on_enter(engine_state);
    }

    // init nuklear
    nuklear_init(engine_state);

    // main game loop
    while (engine_state->is_running) {

        uint64_t current_time = SDL_GetTicksNS();
        uint64_t elapsed_time_ns = current_time - engine_state->previous_time;

        // reset previous time for the next frame's calculation
        engine_state->previous_time = current_time;

        //convert elapsed nanoseconds into standard fractional second
        double frame_time = (double) elapsed_time_ns / NS_PER_SECOND;

        // cap the frame to prevent Spiral of Death
        if(frame_time > 0.25){
            frame_time = 0.25;
        }

        accumulator += frame_time;

        /// process events
        SDL_Event event;
        // pool the operating system for events
        while(SDL_PollEvent(&event)){
            process_input(&event,engine_state);
            process_window_events(&event,engine_state);


            // nuklear events
            SDL_ConvertEventToRenderCoordinates(engine_state->renderer, &event);
            nuklear_event(engine_state->nk_ctx,&event);
        }

        // nuklear update

        if(engine_state->editor.is_editor){
            nuklear_update(engine_state);
        }

        /// process raw input
        const bool* key_state = SDL_GetKeyboardState(NULL);
        input_update_state(&engine_state->input_state,&engine_state->input_mapper,key_state);

        while (accumulator >= FIXED_TIME_STEP) {
            // update(engine_state, FIXED_TIME_STEP);

            if(engine_state->active_state.update){
                engine_state->active_state.update(FIXED_TIME_STEP,engine_state);
            }

            accumulator -= FIXED_TIME_STEP;
        }

        /// render
        // render(engine_state);
        if(engine_state->active_state.render){

            // set background collor
            SDL_SetRenderDrawColor(engine_state->renderer,30,30,30,SDL_ALPHA_OPAQUE);

            // clear screen with the set color
            SDL_RenderClear(engine_state->renderer);

            /// ----------------------------------------------------
            ///     DRAW CALLS GOES HERE (MENU AND GAMEPLAY)
            /// ----------------------------------------------------
            engine_state->active_state.render(engine_state);
            /// ----------------------------------------------------
            ///

            // microui
            // if(engine_state->edit_menu){
            //     window_microui(engine_state);
            //     // mu_widgets_extra_render(engine_state);
            // }

            // nuklear GUI
            if(engine_state->editor.is_editor){
                nk_sdl_render(engine_state->nk_ctx, engine_state->AA);
                nk_sdl_update_TextInput(engine_state->nk_ctx);
            }

            // Swap the back buffer to the front
            SDL_RenderPresent(engine_state->renderer);
        }

        // get the time that the frame end it's work
        uint64_t frame_end_time = SDL_GetTicksNS();

        // calculate how long it took to finish the work
        uint64_t time_spent_working = frame_end_time - current_time;

        // cap the framerate
        if(time_spent_working < TARGET_FPS_TIME_NS){
            // calculate the leftover time
            uint64_t sleep_time = TARGET_FPS_TIME_NS - time_spent_working;

            // command to put the main tread to sleep
            SDL_DelayNS(sleep_time);
        }

        if(engine_state->editor.is_editor){
            nk_input_begin(engine_state->nk_ctx);
        }
    }

    // on exit state
    engine_state->active_state.on_exit(engine_state);

    // destroy window and shut down
    if(engine_state->renderer != NULL){
        SDL_DestroyRenderer(engine_state->renderer);
    }

    if(engine_state->window != NULL){
        SDL_DestroyWindow(engine_state->window);
    }

    // nuklear
    nk_input_end(engine_state->nk_ctx);
    nk_sdl_shutdown(engine_state->nk_ctx);

    SDL_Quit();



    free(engine_state);

    return 0;
}
