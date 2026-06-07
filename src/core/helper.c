#include "helper.h"

void helper_overlap_rect(const SDL_FRect *a, const SDL_FRect *b, SDL_FPoint *overlap)
{
    float a_left = a->x;
    float a_right = a->x + a->w;
    float a_top = a->y;
    float a_bottom = a->y + a->h;

    float b_left = b->x;
    float b_right = b->x + b->w;
    float b_top = b->y;
    float b_bottom = b->y + b->h;

    bool over_x = (a_right > b_left) && (a_left < b_right);
    bool over_y = (a_bottom > b_top) && (a_top < b_bottom);

    // x overlap
    float x_overlap_left = 0;

    if(over_x && over_y){
        // TraceLog(LOG_INFO,"OVERLAP!");
    }else{
        // TraceLog(LOG_INFO,"NO OVERLAP!");
    }
}

SDL_FRect helper_get_overlap(const SDL_FRect *a, const SDL_FRect *b){
    float x = SDL_max(a->x, b->x);
    float y = SDL_max(a->y, b->y);
    float z = SDL_min(a->x + a->w, b->x + b->w);
    float w = SDL_min(a->y + a->h, b->y + b->h);

    return (SDL_FRect){x,y,z-x,w-y};
}


bool helper_intersects_aabb(const SDL_FRect *a, const SDL_FRect *b){

    if(a->x >= (b->x + b->w)) return false;
    if(a->y >= (b->y + b->h)) return false;

    if(a->x + a->w <= b->x) return false;
    if(a->y + a->h <= b->y) return false;

    return true;
}

float helper_vector_lenght(const SDL_FPoint vector){
    return SDL_sqrtf((vector.x * vector.x) + (vector.y * vector.y));
}