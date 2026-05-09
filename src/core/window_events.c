#include "window_events.h"


void process_window_events(SDL_Event *event, EngineState *state){

        switch (event->type) {
        case SDL_EVENT_QUIT:
            state->is_running = false;
            break;
        case SDL_EVENT_WINDOW_FOCUS_GAINED:
            state->has_focus = true;
            break;
        case SDL_EVENT_WINDOW_FOCUS_LOST:
            state->has_focus = false;
            break;
        // case SDL_EVENT_WINDOW_RESIZED:{
        //     int new_width = event->window.data1;
        //     int new_height = event->window.data2;

        //     // update state
        //     state->window_width = new_width;
        //     state->window_height = new_height;

        //     state->camera.offset_x = state->window_width * 0.5f;
        //     state->camera.offset_y = state->window_height * 0.5f;
        //     // state->camera.offset_x = -new_width * 0.5f;
        //     // state->camera.offset_y = -new_height * 0.5f;

        //     // update window matrix
        //     // sync renderer (passing null resets the viewport to the full current window size)
        //     SDL_SetRenderViewport(state->renderer, NULL);

        //     break;
        // }
        case SDL_EVENT_WINDOW_RESIZED:
        case SDL_EVENT_WINDOW_DISPLAY_CHANGED: {
            // int w, h;
            // SDL_GetWindowSizeInPixels(state->window, &w, &h);
            // state->window_width    = w;
            // state->window_height   = h;
            // state->camera.offset_x = w * 0.5f;
            // state->camera.offset_y = h * 0.5f;

            // SDL_SetRenderLogicalPresentation(state->renderer, w, h, SDL_LOGICAL_PRESENTATION_LETTERBOX);
            SDL_SetRenderViewport(state->renderer, NULL);

            break;
        }
        case SDL_EVENT_WINDOW_MOVED:
        case SDL_EVENT_WINDOW_MINIMIZED:{
            state->is_paused = true;
            break;
        }
        case SDL_EVENT_WINDOW_RESTORED:
        case SDL_EVENT_WINDOW_EXPOSED:{
            state->is_paused = false;
            state->previous_time = SDL_GetTicksNS();
            break;
        }
    }
}
