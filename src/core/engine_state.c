#include "engine_state.h"

#include "process_input.h"
#include "microui_helpers.h"

void engine_state_initialize_graphics(EngineState *self){

    /// init window
    SDL_PropertiesID props = SDL_CreateProperties();
    SDL_SetStringProperty(props, SDL_PROP_WINDOW_CREATE_TITLE_STRING, "Engine Core");
    SDL_SetNumberProperty(props, SDL_PROP_WINDOW_CREATE_WIDTH_NUMBER, self->window_width);
    SDL_SetNumberProperty(props, SDL_PROP_WINDOW_CREATE_HEIGHT_NUMBER, self->window_height);
    SDL_SetNumberProperty(props, SDL_PROP_WINDOW_CREATE_X_NUMBER, SDL_WINDOWPOS_CENTERED);
    SDL_SetNumberProperty(props, SDL_PROP_WINDOW_CREATE_Y_NUMBER, SDL_WINDOWPOS_CENTERED);
    self->window = SDL_CreateWindowWithProperties(props);

    if(self->window == NULL){
        printf("Failed to create window: %s\n",SDL_GetError());
    }


    SDL_SetWindowResizable(self->window,true);

    /// init renderer
    self->renderer = SDL_CreateRenderer(self->window, NULL);

    if(self->renderer == NULL){
        printf("Failed to create renderer: %s\n",SDL_GetError());
    }


    // set logical presentation size
    if(!SDL_SetRenderLogicalPresentation(self->renderer,self->window_width,self->window_height,SDL_LOGICAL_PRESENTATION_LETTERBOX)){
        printf("Logical presentation error: %s\n",SDL_GetError());
    }

    // enable alpha blending for png's
    SDL_SetRenderDrawBlendMode(self->renderer,SDL_BLENDMODE_BLEND);

    // init asset manager
    asset_manager_init(&self->asset_manager);
    asset_manager_load_all(&self->asset_manager,self->renderer);

    // clear states
    game_state_init(&self->gameplay);
    game_state_init(&self->menu);

    //keyboard
    input_init_defaults(&self->input_mapper);

    // camera
    self->camera.zoom = 16*4; // to set positioning 16 to 1
    self->camera.x = 0.0f;
    self->camera.y = 0.0f;
    self->camera.offset_x = self->window_width * 0.5f;
    self->camera.offset_y = self->window_height * 0.5f;

    // player
    self->player_ref = null_entity();

    //editor
    self->edit_menu = true;
    memset(self->selected_layer,0,sizeof(self->selected_layer));
}

void engine_state_init_microui(EngineState *self){
    self->ctx = malloc(sizeof(mu_Context));
    mu_init(self->ctx);

    self->ctx->text_height = text_height;
    self->ctx->text_width = text_width;

    mu_begin(self->ctx);

    // clear array self->pending_images
    memset(self->pending_images,0,sizeof(self->pending_images));
    self->pending_images_count = 0;
}

void engine_state_init(EngineState *self)
{
    self->is_running = true;
    self->has_focus = false;
    self->window = NULL;
    self->renderer = NULL;

    self->window_width = 1280;
    self->window_height = 720;

    self->is_paused = false;

    // initialize graphics context
    engine_state_initialize_graphics(self);

    // initialize microui
    engine_state_init_microui(self);

    // clear current state set to NULL
    game_state_init(&self->active_state);
    game_state_init(&self->gameplay);
    game_state_init(&self->menu);
}

// todo maybe update separate
void engine_state_pending_images_add(EngineState *engine_state, PendingImage pending_image)
{

    // SDL_Log("pending count:%i",engine_state->pending_images_count);

    // do we have that image already?
    for (int i = 0; i < engine_state->pending_images_count; ++i) {
        if(pending_image.widget_id == engine_state->pending_images[i].widget_id){

            engine_state->pending_images[i].destination_rect = pending_image.destination_rect;
            engine_state->pending_images[i].mu_flags = pending_image.mu_flags;

            // check hover
            if(engine_state->pending_images[i].widget_id == engine_state->ctx->hover ){

            }

            // just check the state and update -> return

            return;
        }
    }


    // if not put in the array to be renderef after
    engine_state->pending_images[engine_state->pending_images_count++] = pending_image;
}
