#ifndef COMPONENTS_H
#define COMPONENTS_H

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
    int previous_collisions_count;

} ColliderComponent;

typedef struct {
    // TextureAsset *texture_asset = nullptr;
    int asset_texture_index;
    int texture_index;
    float angle;
    // Vector2 render_origin = {0};
    // RenderLayer layer = RenderLayer::DEFAULT;
}SpriteComponent;

// struct PhysicsComponent{
//     Vector2 velocity = {};
//     Vector2 acceleration = {};
//     float max_speed = 0;
//     float move_force = 0;
// };

// struct HealthComponent{
//     bool active = false;
//     float max_health;
//     float current_health;
// };

// struct AttackComponent{
//     float damage = 1;
//     float cooldown = 1.0f; // 1 attack per second
//     float cooldown_counter = 0.0f;
// };

// struct AnimationComponent{
//     bool active = false;
//     int startFrame = {};
//     int lastFrame = {};
//     int currentFrame = {};
//     int frameOffset = {};
//     int frameCount = 2; // for now

//     // counter for any animation
//     float animationCounter = 0;

//     // specific animation type (loop)
//     float idleDuration = 0;// duration per frame
//     float runDuration = 0;

//     // sets for default animation
//     bool defaultAnimation = false;
//     float defaultDuration = 0;

//     // deactivate entity when animation is finished
//     bool deactivateOnFinish = false;

//     // queue free when animation is finished
//     bool deleteOnFinish = false;
// };

#endif // COMPONENTS_H
