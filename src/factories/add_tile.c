#include "add_tile.h"

EntityRef add_tile(EntityManager *entity_manager, float x, float y, MapLayer map_layer)
{
    EntityRef ref = entity_manager_add(entity_manager,KIND_TILE);
    Entity *e = entity_manager_get(entity_manager,ref);

    e->pos = (SDL_FPoint){x,y};
    e->map_layer = map_layer;

    e->sprite.asset_texture_index = 0;
    e->sprite.texture_index = 0;
    e->map_layer = map_layer; // map layer is the same as render_layer

    e->collider.width   = 1.0f;
    e->collider.height  = 1.0f;

    return ref;
}
