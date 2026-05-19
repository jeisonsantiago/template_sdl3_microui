#include "map.h"

// row    = index / width
// column = index % width
// index = (row * width) + column

int get_map_index(Map*self, int x, int y){
    return (y * self->cols) + x;
}

void map_init(Map *self, int rows, int cols)
{
    if(rows > 0 && rows <= 100 && cols > 0 && cols <=100){
        self->rows = rows;
        self->cols = cols;
    }

    // clear all with zeros
    // memset(self->map_data,0,sizeof(self->map_data));
    for (int i = 0; i < MAP_LAYER_COUNT; ++i) {
        for (int j = 0; j < MAX_MAP_SIZE; ++j) {
            self->map_data[i][j] = invalid_entity_ref();
        }
    }
}

void map_clear_data(Map *self)
{
    self->rows = 0;
    self->cols = 0;


    // clear all with zeros
    // memset(self->map_data,0,sizeof(self->map_data));
    for (int i = 0; i < MAP_LAYER_COUNT; ++i) {
        for (int j = 0; j < MAX_MAP_SIZE; ++j) {
            self->map_data[i][j] = invalid_entity_ref();
        }
    }
}

void map_clear(Map *self, int x, int y, MapLayer map_layer){
    if(!map_is_inside(self,x,y)) return;
    int index = get_map_index(self,x,y);
    self->map_data[map_layer][index] = (EntityRef){INVALID_IDX,INVALID_IDX};
}

void map_set(Map *self, int x, int y, MapLayer map_layer, EntityRef ref)
{
    // we are not checkin for now...
    if(!map_is_inside(self,x,y)) return;
    int index = get_map_index(self,x,y);
    self->map_data[map_layer][index] = ref;
}

EntityRef map_get(Map *self, int x, int y, MapLayer map_layer)
{
    if(!map_is_inside(self,x,y)) return invalid_entity_ref();
    int index = get_map_index(self,x,y);
    return self->map_data[map_layer][index];
}

bool map_is_inside(Map *self, int x, int y)
{
    return  !(x < 0 || x >= self->cols || y < 0 || y >= self->rows);
}
