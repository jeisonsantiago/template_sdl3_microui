#include "add_tile.h"

EntityRef add_tile(EntityManager *entity_manager, float x, float y)
{
    EntityRef ref = entity_manager_add(entity_manager,KIND_TILE);
    Entity *e = entity_manager_get(entity_manager,ref);

    e->pos = (SDL_FPoint){x,y};

    e->sprite.asset_texture_index = 0;
    e->sprite.texture_index = 0;


    return ref;
}
