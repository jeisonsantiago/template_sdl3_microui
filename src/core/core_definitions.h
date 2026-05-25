#ifndef CORE_DEFINITIONS_H
#define CORE_DEFINITIONS_H

typedef enum {
    KIND_NIL,
    KIND_PLAYER,
    KIND_ENEMY,
    KIND_WEAPON,
    KIND_PARTICLE,
    KIND_ITEM,
    KIND_TILE,
}Kind;

// map layer and render layer are the same thing
typedef enum{
    MAP_LAYER_GROUND = 0,
    MAP_LAYER_SOLID,
    MAP_LAYER_DECORATION_BG,
    MAP_LAYER_ACTORS,
    MAP_LAYER_Y_SORT,
    MAP_LAYER_DECORATION_FG,
    MAP_LAYER_COUNT
}MapLayer;

#endif // CORE_DEFINITIONS_H
