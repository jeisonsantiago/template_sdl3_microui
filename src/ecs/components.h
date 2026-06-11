#ifndef COMPONENTS_H
#define COMPONENTS_H

#include "core_definitions.h"

// typedef enum{
//     RENDER_LAYER_GROUND,
//     RENDER_LAYER_SOLID,
//     RENDER_LAYER_DECORATION,
//     RENDER_LAYER_PLAYER,
//     RENDER_LAYER_ENEMY,
//     RENDER_LAYER_COUNT
// }RenderLayer;

typedef enum{
    COLLIDER_TYPE_TRIGGER = 0,
    COLLIDER_TYPE_SOLID = 0,
}PhysicsBody;

typedef struct {
    SDL_FPoint position;
}TransformComponent;

typedef struct {
    bool active;
    float width;
    float height;
    bool is_trigger;

    SDL_FPoint offset;

    uint16_t layer; // which layer the entity belongs
    uint16_t mask; // which mask the entity will interact with

    int current_collisions[10];
    int current_collisions_count;
    int previous_collisions[10];
    // int previous_collisions_count;

} ColliderComponent;

typedef struct {
    // TextureAsset *texture_asset = nullptr;
    int asset_texture_index;
    int texture_index;
    float angle;
    MapLayer render_layer;
    // Vector2 render_origin = {0};
    // RenderLayer layer = RenderLayer::DEFAULT;
}SpriteComponent;

typedef struct{
    SDL_FPoint velocity;
    SDL_FPoint acceleration;
    float speed;
    float friction;
}PhysicsComponent;

typedef struct {
    bool active;
    float max_health;
    float current_health;
}HealthComponent;

typedef struct {
    float damage;
    float cooldown; // 1 attack per second
    float cooldown_counter;
}AttackComponent;

typedef struct{
    bool active;

    int base_frame_index;
    int frame_counter;
}AnimationComponent;

#endif // COMPONENTS_H
