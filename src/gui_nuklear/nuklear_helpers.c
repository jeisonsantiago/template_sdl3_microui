#include "nuklear_helpers.h"

#define NK_IMPLEMENTATION
#include "nuklear.h"
#define NK_SDL3_RENDERER_IMPLEMENTATION
#include "nuklear_sdl3_renderer.h"

// #define WINDOW_WIDTH 1280
// #define WINDOW_HEIGHT 720

#include "asset_manager.h"
#include "editor.h"

#include "serialization_map.h"

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

    // init input
    nk_input_begin(ctx);
}

void nuklear_event(struct nk_context *ctx, SDL_Event *event)
{
    nk_sdl_handle_event(ctx,event);
}

static void ui_header(struct nk_context *ctx, const char *title)
{
    nk_layout_row_dynamic(ctx, 20, 1);
    nk_label(ctx, title, NK_TEXT_LEFT);
}

static void ui_widget(struct nk_context *ctx, float height)
{
    // static const float ratio[] = {0.05f, 0.85f};
    static const float ratio[] = {0.0f, 0.75f};
    nk_layout_row(ctx, NK_DYNAMIC, height, 2, ratio);
    nk_spacing(ctx, 1);
}

static void ui_widget_centered(struct nk_context *ctx, float height)
{
    static const float ratio[] = {0.15f, 0.50f, 0.35f};
    // nk_style_set_font(ctx, &media->font_22->handle);
    nk_layout_row(ctx, NK_DYNAMIC, height, 3, ratio);
    nk_spacing(ctx, 1);
}

static struct nk_image ui_image_from_texture(TextureAsset *texture_asset, struct nk_rect region){
    struct nk_image img = nk_subimage_ptr(
                texture_asset->texture,
                texture_asset->texture->w,
                texture_asset->texture->h,
                region);



    return img;
}

static struct nk_image ui_image_from_texture_ex(TextureAsset *texture_asset, int index){

    SDL_FRect texture_region = asset_manager_get_texture_rect_by_index(index,texture_asset);

    struct nk_image img = nk_subimage_ptr(
                texture_asset->texture,
                texture_asset->texture->w,
                texture_asset->texture->h,
                nk_rect(texture_region.x, texture_region.y, texture_region.w,texture_region.h));

    return img;
}

void nuklear_gui(EngineState *engine_state){


    struct nk_context *ctx = engine_state->nk_ctx;

    ui_header(ctx,"Camera Zoom:");

    ui_header(ctx,"Layers:");
    int i = 0;
    ui_widget(ctx,30);
    if (nk_combo_begin_label(ctx, layer_to_string(engine_state->editor.selected_layer), nk_vec2(nk_widget_width(ctx), 200))) {
        nk_layout_row_dynamic(ctx, 35, 1);
        for (i = 0; i < MAP_LAYER_COUNT; ++i)
            if (nk_combo_item_label(ctx, layer_to_string(i), NK_TEXT_LEFT))
                engine_state->editor.selected_layer = i;
        nk_combo_end(ctx);
    }

    ui_header(ctx,"");
    nk_layout_row_static(ctx,40,40,2);
    nk_label(ctx,"Tile:",NK_TEXT_ALIGN_LEFT);

    // struct nk_image img = ui_image_from_texture(&engine_state->asset_manager.texture_assets[0],nk_rect(0,0,16,16));
    struct nk_image img =
            ui_image_from_texture_ex(
                &engine_state->asset_manager.texture_assets[0],
                engine_state->editor.selected_tile
                );


    nk_image(ctx,img);

    //
    ui_header(ctx,"");
    if (nk_tree_push(ctx, NK_TREE_NODE, "Tiles:", NK_MINIMIZED )) {
        nk_layout_row_static(ctx,40,40,10);

        TextureAsset *tasset = &engine_state->asset_manager.texture_assets[0];

        // if(nk_button_)
        for (int i = 0; i < tasset->tile_count; ++i) {
            struct nk_image img = ui_image_from_texture_ex(&engine_state->asset_manager.texture_assets[0],i);


            char label[4];
            sprintf(label,"%i",i);
            nk_label(ctx,label,0);
            if(nk_button_image(ctx,img)){
            // if(nk_button_image_label(ctx,img,"TEST",NK_TEXT_LEFT)){
                engine_state->editor.selected_tile = i;
            }


            // nk_layout_row_static(ctx,40,45,2);
            // char label[10] = "11";
            // nk_label(ctx,label,0);
            // if(nk_button_image(ctx,img)){
            // // if(nk_button_image_label(ctx,img,"TEST",NK_TEXT_LEFT)){

            //     engine_state->editor.selected_tile = i;
            // }
        }
        nk_tree_pop(ctx);
    }



    // nk_menubar_begin(ctx);
    // {
    //     /* toolbar */
    //     // nk_layout_row_static(ctx, 40, 40, 4);
    //     nk_layout_row_static(ctx, 40, 40, 4);
    //     if(nk_button_label(ctx,"Test")){}

    // }
    // nk_menubar_end(ctx);

    ui_header(ctx,"");


    nk_layout_row_static(ctx, 30, 80, 2);
    if (nk_button_label(ctx, "Save Map")) {
        SDL_Log("button pressed");
        serialization_save_map(engine_state,"map_01.bin");
    }
    if (nk_button_label(ctx, "Load Map")) {
        SDL_Log("button pressed");
    }

    // nk_layout_row_dynamic(ctx, 30, 2);
    // if (nk_option_label(ctx, "easy", op == EASY)) op = EASY;
    // if (nk_option_label(ctx, "hard", op == HARD)) op = HARD;
    // nk_layout_row_dynamic(ctx, 25, 1);
    // nk_property_int(ctx, "Compression:", 0, &property, 1000, 1, 1);

    // nk_layout_row_dynamic(ctx, 20, 1);
    // nk_label(ctx, "background:", NK_TEXT_LEFT);
    // nk_layout_row_dynamic(ctx, 25, 1);
    // if (nk_combo_begin_color(ctx, nk_rgb_cf(engine_state->bg), nk_vec2(nk_widget_width(ctx),400))) {
    //     nk_layout_row_dynamic(ctx, 120, 1);
    //     engine_state->bg = nk_color_picker(ctx, engine_state->bg, NK_RGBA);
    //     nk_layout_row_dynamic(ctx, 25, 1);
    //     engine_state->bg.r = nk_propertyf(ctx, "#R:", 0, engine_state->bg.r, 1.0f, 0.01f,0.005f);
    //     engine_state->bg.g = nk_propertyf(ctx, "#G:", 0, engine_state->bg.g, 1.0f, 0.01f,0.005f);
    //     engine_state->bg.b = nk_propertyf(ctx, "#B:", 0, engine_state->bg.b, 1.0f, 0.01f,0.005f);
    //     engine_state->bg.a = nk_propertyf(ctx, "#A:", 0, engine_state->bg.a, 1.0f, 0.01f,0.005f);
    //     nk_combo_end(ctx);
    // }
}

void nuklear_update(EngineState *engine_state)
{

    struct nk_context *ctx = engine_state->nk_ctx;
    nk_input_end(ctx);

    if (nk_begin(ctx, "Editor", nk_rect(50, 50, 500, 400),
                 NK_WINDOW_BORDER|NK_WINDOW_MOVABLE|NK_WINDOW_SCALABLE|
                 NK_WINDOW_MINIMIZABLE|NK_WINDOW_TITLE))
    {
        nuklear_gui(engine_state);
    }
    nk_end(ctx);
}
