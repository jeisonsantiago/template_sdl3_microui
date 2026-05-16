#include "add_player.h"


EntityRef add_player(EntityManager *entity_manager)
{
    EntityRef ref = entity_manager_add(entity_manager,KIND_PLAYER);
    Entity *e = entity_manager_get(entity_manager,ref);

    e->pos = (SDL_FPoint){0,0};

    e->sprite.asset_texture_index = 2;
    e->sprite.texture_index = 0;
    e->sprite.render_layer = RENDER_LAYER_PLAYER;

    return ref;
}
