#ifndef CORE_HELPERS_H
#define CORE_HELPERS_H

#define MAX_STRING_SIZE 100

typedef struct{
    char string[MAX_STRING_SIZE];
    size_t size;
}LameString;

void core_int_to_str(char *str, int number);

float core_vector_lenght(const SDL_FPoint *vec);

float core_rect_left(const SDL_FRect *rect);
float core_rect_right(const SDL_FRect *rect);

float core_rect_top(const SDL_FRect *rect);
float core_rect_bottom(const SDL_FRect *rect);

#endif // CORE_HELPERS_H
