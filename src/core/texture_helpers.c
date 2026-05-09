#include "texture_helpers.h"

struct SDL_Texture *texture_load(struct SDL_Renderer *renderer, const char *file_path){

    // load file and decode it into Surface
    SDL_Surface *temp_surface = IMG_Load(file_path);
    if(temp_surface == NULL){
        printf("Unable to load image [%s], error: %s\n",file_path,SDL_GetError());
        return NULL;
    }

    // upload pixels from surface to a texture
    SDL_Texture * new_texture = SDL_CreateTextureFromSurface(renderer,temp_surface);
    SDL_SetTextureScaleMode(new_texture,SDL_SCALEMODE_PIXELART);


    // clean up temp
    SDL_DestroySurface(temp_surface);

    if(new_texture == NULL){
        printf("Unable to load image as texture [%s], error: %s\n",file_path,SDL_GetError());
        return NULL;
    }

    SDL_Log("Texture [%s] Loaded",file_path);
    return new_texture;
}

void texture_get_dimensions(SDL_Texture *texture, float *width, float *height)
{
    SDL_GetTextureSize(texture,width,height);
}

void texture_free(struct SDL_Texture *texture)
{
    if(texture != NULL){
        SDL_DestroyTexture(texture);
    }
}
