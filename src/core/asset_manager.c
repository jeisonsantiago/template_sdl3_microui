#include "asset_manager.h"

#include "texture_helpers.h"
#include "atlas.inl"

void update_tile_count(TextureAsset *texture_asset){
    texture_asset->tile_count_cols = (int)texture_asset->texture->w / 16;
    texture_asset->tile_count_rows = (int)texture_asset->texture->h / 16;
    texture_asset->tile_count =  texture_asset->tile_count_rows * texture_asset->tile_count_cols;

    texture_asset->tile_size_w = 16;
    texture_asset->tile_size_h = 16;

}

void asset_manager_init(AssetManager *self)
{
    memset(self,0,sizeof(AssetManager));

    // self->world.texture = NULL;
    // self->interface.texture = NULL;
    // self->characters.texture = NULL;
    // self->fx.texture = NULL;
    // self->fx_altered.texture = NULL;
    // self->items_no_shadow.texture = NULL;
}

void asset_manager_load_all(AssetManager *self, SDL_Renderer *renderer)
{
    self->world.texture = texture_load(renderer,RESOURCES_PATH "images/tiny_dungeon_world.png");
    update_tile_count(&self->world);

    self->interface.texture  = texture_load(renderer,RESOURCES_PATH "images/tiny_dungeon_interface.png");
    update_tile_count(&self->interface);

    self->characters.texture  = texture_load(renderer,RESOURCES_PATH "images/tiny_dungeon_monsters.png");
    update_tile_count(&self->characters);

    self->fx.texture  = texture_load(renderer,RESOURCES_PATH "images/tiny_dungeon_fx.png");
    update_tile_count(&self->fx);

    self->fx_altered.texture  = texture_load(renderer,RESOURCES_PATH "images/tiny_dungeon_fx_altered.png");
    update_tile_count(&self->fx_altered);

    self->items_no_shadow.texture  = texture_load(renderer,RESOURCES_PATH "images/tiny_dungeon_items_no_shadow.png");
    update_tile_count(&self->items_no_shadow);


    // // microui
    unsigned char pixels[128*128*4];

    int c = 0;
    for(int i = 0; i < 128 * 128; i++) {
        pixels[c] = atlas_texture[i];
        pixels[c+1] = atlas_texture[i];
        pixels[c+2] = atlas_texture[i];
        pixels[c+3] = 255;
        c+=4;
    }

    SDL_Surface *sur = SDL_CreateSurfaceFrom(128, 128, SDL_PIXELFORMAT_XRGB8888, pixels, 4 * 128);
    SDL_Texture *tex = SDL_CreateTextureFromSurface(renderer, sur);
    SDL_SetTextureBlendMode(tex, SDL_BLENDMODE_ADD);
    SDL_SetTextureScaleMode(tex,SDL_SCALEMODE_LINEAR);

    SDL_DestroySurface(sur);
    self->microui.texture = tex;


    // this->pixelFont = LoadFont(RESOURCES_PATH "/fonts/pixantiqua.ttf");
}

SDL_FRect asset_manager_get_texture_rect_by_index(int index, TextureAsset *texture_asset)
{

    // row    = index / width
    // column = index % width
    // index = (row * width) + column

    SDL_FRect rect = {};
    int tx_row = index / (texture_asset->texture->w / texture_asset->tile_size_w);
    int tx_col = index % (texture_asset->texture->w / texture_asset->tile_size_h);

    // TraceLog(LOG_INFO,"%i %i",txCol, txRow);

    rect = (SDL_FRect){
        .x = (float)tx_col * texture_asset->tile_size_w,
        .y = (float)tx_row *  texture_asset->tile_size_h,
        .w = (float)texture_asset->tile_size_w,
        .h = (float)texture_asset->tile_size_h
    };

    return rect;
}
