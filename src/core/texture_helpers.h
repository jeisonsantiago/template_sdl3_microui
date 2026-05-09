#ifndef TEXTURE_HELPERS_H
#define TEXTURE_HELPERS_H

SDL_Texture *texture_load(SDL_Renderer *renderer, const char *file_path);
void texture_get_dimensions(SDL_Texture *texture, float *width, float *height);
void texture_free(SDL_Texture *texture);

#endif // TEXTURE_HELPERS_H
