#include "microui_widgets.h"

int incrementer(struct mu_Context *ctx, int *value) {
    mu_Id     id = mu_get_id(ctx, &value, sizeof(value));
    mu_Rect rect = mu_layout_next(ctx);
    mu_update_control(ctx, id, rect, 0);

    /* handle input */
    int res = 0;
    if (ctx->mouse_pressed == MU_MOUSE_LEFT && ctx->focus == id) {
        (*value)++;
        res |= MU_RES_CHANGE;
    }

    /* draw */
    char buf[32];
    sprintf(buf, "%d", *value);
    mu_draw_control_frame(ctx, id, rect, MU_COLOR_BUTTON, 0);
    mu_draw_control_text(ctx, buf, rect, MU_COLOR_TEXT, MU_OPT_ALIGNCENTER);

    return res;
}

int mu_extra_image_button(mu_Context *ctx,EngineState *engine_state,SDL_FRect src, int w, int h, SDL_Texture *texture, int bt_index)
{
    mu_Id     id = mu_get_id(ctx, &bt_index, sizeof(bt_index));
    mu_Rect rect = mu_layout_next(ctx);
    mu_update_control(ctx, id, rect, 0);

    /* handle input */
    int res = 0;
    if (ctx->mouse_pressed == MU_MOUSE_LEFT && ctx->focus == id) {
        res |= MU_RES_CHANGE;
        SDL_Log("pressed");
    }

    // update rect size
    rect.w = w;
    rect.h = h;

    /* draw */
    char buf[32];
    sprintf(buf, "%d", bt_index);
    mu_draw_control_frame(ctx, id, rect, MU_COLOR_BUTTON, 0);
    mu_draw_control_text(ctx, buf, rect, MU_COLOR_TEXT, MU_OPT_ALIGNCENTER);
    // mu_draw_rect(ctx,rect,ctx->style->colors[MU_COLOR_BUTTON]);

    // SDL_FRect destination_rect = {rect.x,rect.y, w,h};
    SDL_FRect destination_rect = {rect.x,rect.y, rect.w,rect.h};
    SDL_FRect source_rect = src;

    // SDL_Log("rect (index:%i): %f %f %f %f",bt_index, src.x, src.y, src.w, src.h);

    PendingImage pending_image = {
        .source_rect = source_rect,
        .destination_rect = destination_rect,
        .texture = texture,
        .widget_id = id,
    };

    pending_image.mu_flags = 0;
    if(ctx->hover == id){
        pending_image.mu_flags |= MU_EXTRA_HOVER;

    }

    // int clipped = mu_check_clip(ctx, rect);
    // if (clipped == MU_CLIP_ALL ) { pending_image.mu_flags |= MU_EXTRA_OUTSIDE; }
    // // if (clipped == MU_CLIP_PART) { mu_set_clip(ctx, mu_get_clip_rect(ctx)); }

    engine_state_pending_images_add(engine_state,pending_image);

    return res;
}

void mu_widgets_extra_render(EngineState *engine_state)
{
    // render microui pending images
    for (int i = 0; i < engine_state->pending_images_count; ++i) {
        PendingImage *pending_img = &engine_state->pending_images[i];

        if(pending_img->mu_flags & MU_EXTRA_OUTSIDE){
            return;
        }

        SDL_RenderTexture(
                    engine_state->renderer,
                    pending_img->texture,
                    &pending_img->source_rect,
                    &pending_img->destination_rect
                    );

        if(pending_img->mu_flags & MU_EXTRA_HOVER){
            SDL_SetRenderDrawColor(engine_state->renderer, 0, 255, 0, SDL_ALPHA_OPAQUE);  /* green, full alpha */
            SDL_RenderRect(engine_state->renderer, &pending_img->destination_rect);  /* draw three rectangles at once */
            SDL_SetRenderDrawColor(engine_state->renderer,30,30,30,SDL_ALPHA_OPAQUE);
        }
    }
}

int mu_extra_image_rect(mu_Context *ctx, EngineState *engine_state, SDL_FRect src, int w, int h, SDL_Texture *texture, int tile_index)
{
    mu_Rect rect = mu_layout_next(ctx);
    rect.w = w;
    rect.h = h;
    mu_draw_rect(ctx,rect,ctx->style->colors[MU_COLOR_BUTTON]);

    SDL_FRect destination_rect = {rect.x,rect.y, rect.w,rect.h};
    SDL_FRect source_rect = src;

    PendingImage pending_image = {
        .source_rect = source_rect,
        .destination_rect = destination_rect,
        .texture = texture,
        .widget_id = -1,
    };

    engine_state_pending_images_add(engine_state,pending_image);

    return 0;
}
