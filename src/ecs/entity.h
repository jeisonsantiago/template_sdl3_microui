#ifndef ENTITY_H
#define ENTITY_H

#include "components.h"

typedef struct {
    uint32_t idx;
    uint32_t gen;
}EntityRef;

typedef enum {
    KIND_NIL,
    KIND_PLAYER,
    KIND_ENEMY,
    KIND_WEAPON,
    KIND_PARTICLE,
    KIND_ITEM,
    KIND_TILE,
}Kind;

typedef struct {
    Kind kind;
    SDL_FPoint pos;
    bool active;
    bool queue_free;

    // components
    ColliderComponent collider;
    SpriteComponent sprite;

    EntityRef parent_ref;
    EntityRef first_child_ref;
    EntityRef next_sibling_ref;
    EntityRef previous_sibling_ref;

    // collision related
    // std::function<void(int,int, EntityArray&)> on_collision_enter = nullptr;
    void (*on_collion_enter)(uint32_t,uint32_t,void *entity_manager);
    // std::function<void(int,int, EntityArray&)> on_collision_stay = nullptr;
    void (*on_collion_stay)(uint32_t,uint32_t,void *entity_manager);
    // std::function<void(int,int, EntityArray&)> on_collision_exit = nullptr;
    void (*on_collion_exit)(uint32_t,uint32_t,void *entity_manager);

    // bool has_child(int idx);
}Entity;

bool entity_valid(Entity *self);
// operator bool() const{
//     return kind != Kind::Nil;
// }



#endif // ENTITY_H
