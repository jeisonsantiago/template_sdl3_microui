#include "nuklear_helpers.h"

#define NK_IMPLEMENTATION
#include "nuklear.h"
#define NK_SDL3_RENDERER_IMPLEMENTATION
#include "nuklear_sdl3_renderer.h"

// #define WINDOW_WIDTH 1280
// #define WINDOW_HEIGHT 720

static char* nk_sdl_dtoa(char *str, double d)
{
    NK_ASSERT(str);
    if (!str) return NULL;
    (void)SDL_snprintf(str, 99999, "%.17g", d);
    return str;
}
void nuklear_init(EngineState *engine_state)
{
    engine_state->nk_ctx = nk_sdl_init(engine_state->window,engine_state->renderer,nk_sdl_allocator());

    struct nk_context *ctx = engine_state->nk_ctx;

    /* If you don't want to use advanced Nuklear font baking API
     * you can use simple ASCII debug font provided by SDL
     * just change the `#if 0` above to `#if 1` */
    nk_sdl_style_set_debug_font(ctx);

    /* Note that since debug font is extremely small (only 8x8 pixels),
     * scaling it does not make much sense. The font would appear blurry. */
    // NK_UNUSED(font_scale);

    /* You may wish to change a few style options, here are few recommendations: */
    ctx->style.button.rounding = 0.0f;
    ctx->style.menu_button.rounding = 0.0f;
    ctx->style.property.rounding = 0.0f;
    ctx->style.property.border = 0.0f;
    ctx->style.option.border = -1.0f;
    ctx->style.checkbox.border = -1.0f;
    ctx->style.property.dec_button.border = -2.0f;
    ctx->style.property.inc_button.border = -2.0f;
    ctx->style.tab.tab_minimize_button.border = -2.0f;
    ctx->style.tab.tab_maximize_button.border = -2.0f;
    ctx->style.tab.node_minimize_button.border = -2.0f;
    ctx->style.tab.node_maximize_button.border = -2.0f;
    ctx->style.checkbox.spacing = 5.0f;
    engine_state->AA = NK_ANTI_ALIASING_OFF;


    engine_state->bg.r = 0.10f;
    engine_state->bg.g = 0.18f;
    engine_state->bg.b = 0.24f;
    engine_state->bg.a = 1.0f;
    /* It's better to disable anti-aliasing when using small fonts */
    // app->AA = NK_ANTI_ALIASING_OFF;

    // init input
    nk_input_begin(ctx);
}

void nuklear_event(struct nk_context *ctx, SDL_Event *event)
{
    nk_sdl_handle_event(ctx,event);
}

void nuklear_update(EngineState *engine_state)
{

    struct nk_context *ctx = engine_state->nk_ctx;
    nk_input_end(ctx);

    if (nk_begin(ctx, "Demo", nk_rect(50, 50, 230, 250),
                 NK_WINDOW_BORDER|NK_WINDOW_MOVABLE|NK_WINDOW_SCALABLE|
                 NK_WINDOW_MINIMIZABLE|NK_WINDOW_TITLE))
    {
        enum {EASY, HARD};
        static int op = EASY;
        static int property = 20;

        nk_layout_row_static(ctx, 30, 80, 1);
        if (nk_button_label(ctx, "button")) {
            SDL_Log("button pressed");
        }
        nk_layout_row_dynamic(ctx, 30, 2);
        if (nk_option_label(ctx, "easy", op == EASY)) op = EASY;
        if (nk_option_label(ctx, "hard", op == HARD)) op = HARD;
        nk_layout_row_dynamic(ctx, 25, 1);
        nk_property_int(ctx, "Compression:", 0, &property, 1000, 1, 1);

        nk_layout_row_dynamic(ctx, 20, 1);
        nk_label(ctx, "background:", NK_TEXT_LEFT);
        nk_layout_row_dynamic(ctx, 25, 1);
        if (nk_combo_begin_color(ctx, nk_rgb_cf(engine_state->bg), nk_vec2(nk_widget_width(ctx),400))) {
            nk_layout_row_dynamic(ctx, 120, 1);
            engine_state->bg = nk_color_picker(ctx, engine_state->bg, NK_RGBA);
            nk_layout_row_dynamic(ctx, 25, 1);
            engine_state->bg.r = nk_propertyf(ctx, "#R:", 0, engine_state->bg.r, 1.0f, 0.01f,0.005f);
            engine_state->bg.g = nk_propertyf(ctx, "#G:", 0, engine_state->bg.g, 1.0f, 0.01f,0.005f);
            engine_state->bg.b = nk_propertyf(ctx, "#B:", 0, engine_state->bg.b, 1.0f, 0.01f,0.005f);
            engine_state->bg.a = nk_propertyf(ctx, "#A:", 0, engine_state->bg.a, 1.0f, 0.01f,0.005f);
            nk_combo_end(ctx);
        }
    }
    nk_end(ctx);
}
