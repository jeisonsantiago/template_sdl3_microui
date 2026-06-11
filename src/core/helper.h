#ifndef HELPER_H
#define HELPER_H


void helper_overlap_rect(const SDL_FRect *a, const SDL_FRect *b, SDL_FPoint *overlap);
bool helper_intersects_aabb(const SDL_FRect *a, const SDL_FRect *b);
SDL_FRect helper_get_overlap(const SDL_FRect *a, const SDL_FRect *b);
float helper_vector_lenght(const SDL_FPoint vector);
// void helper_text_to_buffer(const char *src, const char*)


#endif // HELPER_H
