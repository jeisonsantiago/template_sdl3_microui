#include "core_helpers.h"


void core_int_to_str(char *str, int number)
{
    sprintf(str,"%i",number);
}

float core_vector_lenght(const SDL_FPoint *vec){
    return ((vec->x * vec->x) + (vec->y + vec->y));
}


float core_rect_right(const SDL_FRect *rect)
{
    return rect->x + rect->w;
}

float core_rect_left(const SDL_FRect *rect)
{
    return rect->x;
}

float core_rect_top(const SDL_FRect *rect)
{
    return rect->y;
}

float core_rect_bottom(const SDL_FRect *rect)
{
    return rect->y + rect->h;
}