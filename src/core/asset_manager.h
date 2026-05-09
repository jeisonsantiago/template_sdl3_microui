#ifndef ASSET_MANAGER_H
#define ASSET_MANAGER_H

typedef struct {
    SDL_Texture *texture;
    int tile_size_w;
    int tile_size_h;
    int tile_count_rows;
    int tile_count_cols;
    int tile_count;
}TextureAsset;


//anonymous struct inside a union
typedef union{
    struct{
    TextureAsset world;
    TextureAsset interface; // 16 rows 16 cols
    TextureAsset characters; // 16 rows 16 cols
    TextureAsset fx;
    TextureAsset fx_altered;
    TextureAsset items_no_shadow;
    TextureAsset microui;
    };
    TextureAsset texture_assets[7];
}AssetManager;

void asset_manager_init(AssetManager *self);

void asset_manager_load_all(AssetManager *self, SDL_Renderer *renderer);

#endif // ASSET_MANAGER_H
