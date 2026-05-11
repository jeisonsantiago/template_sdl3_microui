#ifndef MICROUI_DEFINITIONS_H
#define MICROUI_DEFINITIONS_H


typedef struct {
    SDL_Texture *texture;
    SDL_FRect source_rect;
    SDL_FRect destination_rect;
    uint16_t mu_flags;
    mu_Id widget_id;
}PendingImage;

typedef enum{
    MU_EXTRA_HOVER      = (1 << 0),
    MU_EXTRA_CLICK      = (1 << 1),
    MU_EXTRA_OUTSIDE    = (1 << 2),
}MU_EXTRA_FLAGS;

#endif // MICROUI_DEFINITIONS_H
