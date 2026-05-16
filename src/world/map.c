#include "map.h"

// row    = index / width
// column = index % width
// index = (row * width) + column

void map_init(Map *self, int rows, int cols)
{
    if(rows > 0 && rows <= 100 && cols > 0 && cols <=100){
        self->rows = rows;
        self->cols = cols;
    }

    // clear all with zeros
    // memset(self->map_data,0,sizeof(self->map_data));
    for (int i = 0; i < MAX_MAP_SIZE; ++i) {
        for (int j = 0; j < MAP_LAYER_COUNT; ++j) {
            self->map_data[j][i] = invalid_entity_ref();
        }
    }
}

void map_clear_data(Map *self)
{
    self->rows = 0;
    self->cols = 0;
    memset(self->map_data,0,sizeof(self->map_data)); // should work lol
}

void map_clear(Map *self, int x, int y, MapLayer map_layer){
    int index = (y * self->cols) + x;
    if(!map_is_inside(self,x,y)) return;
    self->map_data[map_layer][index] = (EntityRef){0,0};
}

void map_set(Map *self, int x, int y, MapLayer map_layer, EntityRef ref)
{
    // we are not checkin for now...
    int index = (y * self->cols) + x;
    if(!map_is_inside(self,x,y)) return;
    self->map_data[map_layer][index] = ref;
}

EntityRef map_get(Map *self, int x, int y, MapLayer map_layer)
{
    int index = (y * self->cols) + x;
    if(!map_is_inside(self,x,y)) return invalid_entity_ref();
    return self->map_data[map_layer][index];
}

bool map_is_inside(Map *self, int x, int y)
{
    int index = (y * self->cols) + x;
    return (x >= 0 && x < self->cols && y >= 0 && y < self->rows);
}

// void save_to_file(Map *self, const char *file_name, EngineState *engine_state)
// {

// }
