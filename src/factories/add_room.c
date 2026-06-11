#include "add_room.h"
#include "map.h"
#include "add_tile.h"

void add_room(EngineState *engine_state){


    Map *map = &engine_state->world_map;
    EntityManager *entity_manager =&engine_state->entity_manager;



    // set map
    int rows = 8;
    int cols = 8;
    map_init(map,rows,cols);

    for (int r = 1; r < (rows-1); ++r) {
        for (int c = 1; c < (cols-1); ++c) {
            EntityRef ref = add_tile(entity_manager,r,c,MAP_LAYER_GROUND);
            Entity *e = entity_manager_get(entity_manager,ref);

            if(e){
                e->sprite.texture_index = 69;
            }
        }
    }

    for (int r = 1; r < (rows-1); ++r) {
        EntityRef ref = add_tile(entity_manager,r,0,MAP_LAYER_SOLID);
        Entity *e = entity_manager_get(entity_manager,ref);

        if(e){
            e->sprite.texture_index = 1;
        }
    }

    for (int c = 1; c < (cols-1); ++c) {
        EntityRef ref = add_tile(entity_manager,c,0,MAP_LAYER_SOLID);
        Entity *e = entity_manager_get(entity_manager,ref);

        if(e){
            e->sprite.texture_index = 1;
        }
    }

    for (int r = 0; r < (rows); ++r) {
        EntityRef ref = add_tile(entity_manager,r,(rows-1),MAP_LAYER_SOLID);
        Entity *e = entity_manager_get(entity_manager,ref);

        if(e){
            e->sprite.texture_index = 1;
        }
    }

    for (int r = 0; r < (rows-1); ++r) {
        EntityRef ref = add_tile(entity_manager,0,r,MAP_LAYER_SOLID);
        Entity *e = entity_manager_get(entity_manager,ref);

        if(e){
            e->sprite.texture_index = 6;
        }

        ref = add_tile(entity_manager,cols-1,r,MAP_LAYER_SOLID);
        e = entity_manager_get(entity_manager,ref);

        if(e){
            e->sprite.texture_index = 6;
        }
    }




    // map_set(map, 20,20,MAP_LAYER_GROUND,)


}