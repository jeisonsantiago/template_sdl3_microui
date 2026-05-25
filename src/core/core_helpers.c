#include "core_helpers.h"


void core_int_to_str(char *str, int number)
{
    sprintf(str,"%i",number);
}

float core_vector_lenght(const SDL_FPoint *vec){
    return ((vec->x * vec->x) + (vec->y + vec->y));
}
