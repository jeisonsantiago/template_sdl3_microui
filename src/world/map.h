#ifndef MAP_H
#define MAP_H

// #include "engine_state.h"
#include "entity.h"
#include "core_definitions.h"

#include "core_helpers.h"

static LameString map_layer_names[MAP_LAYER_COUNT] = {0};

#define MAX_MAP_ROWS 100
#define MAX_MAP_COLS 100
#define MAX_MAP_SIZE (MAX_MAP_ROWS * MAX_MAP_COLS)

typedef struct{
    int rows;
    int cols;
    EntityRef map_data[MAP_LAYER_COUNT][MAX_MAP_SIZE]; // maximun map size is 100 x 100
}Map;

void map_init(Map *self, int rows, int cols);
void map_clear_data(Map *self);
void map_clear(Map *self, int x, int y, MapLayer map_layer);
void map_set(Map *self, int x, int y, MapLayer map_layer, EntityRef ref);
EntityRef map_get(Map *self, int x, int y, MapLayer map_layer);
bool map_is_inside(Map *self, int x, int y);

#endif // MAP_H
