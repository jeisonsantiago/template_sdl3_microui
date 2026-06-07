#include "add_player.h"


EntityRef add_player(EntityManager *entity_manager, float x, float y, MapLayer map_layer)
{
    EntityRef ref = entity_manager_add(entity_manager,KIND_PLAYER);
    Entity *e = entity_manager_get(entity_manager,ref);

    e->pos = (SDL_FPoint){x,y};
    e->map_layer = map_layer;

    e->collider.width   = 0.5f;
    e->collider.height  = 0.5f;

    // e->collider.width   = 1.0f;
    // e->collider.height  = 1.0f;

    e->collider.offset.x = 0.25f;
    e->collider.offset.y = 0.45f;

    // e->collider.offset.x = 0.0f;
    // e->collider.offset.y = 0.0f;

    e->sprite.asset_texture_index = 2;
    e->sprite.texture_index = 0;
    e->sprite.render_layer = map_layer;

    e->physics.friction = 10.0f;
    e->physics.speed = 20.0f;

    e->physics.acceleration.x = 0;
    e->physics.acceleration.y = 0;
    e->physics.velocity.x = 0;
    e->physics.velocity.y = 0;

    return ref;
}
