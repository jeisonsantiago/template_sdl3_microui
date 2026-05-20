#include "serialization_map.h"


static int VERSION = 1;

int serialization_save_map(EngineState *engine_state, const char *file_name)
{

    Map *map = &engine_state->world_map;
    EntityManager *entity_manager = &engine_state->entity_manager;


    char buffer[200] = {0};
    sprintf(buffer,"%smaps/%s",RESOURCES_PATH,file_name);
    FILE* file = fopen(buffer, "wb");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    fwrite(&VERSION,sizeof(VERSION),1,file);

    // save map config
    fwrite(map,sizeof(Map),1,file);

    // save entities
    // sort the EntityRef, get all from entity_manager and save them

    // get tile count
    int tile_counter = 0;
    for (int i = 0; i < entity_manager->highest_idx; ++i) {
        Entity *e = entity_manager_get_by_index(entity_manager,i);
        if(e->kind == KIND_TILE && entity_manager->used[i]){
            tile_counter++;
        }
    }

    // save tile counter
    fwrite(&tile_counter,sizeof(tile_counter),1,file);

    for (int i = 0; i < entity_manager->highest_idx; ++i) {
        Entity *e = entity_manager_get_by_index(entity_manager,i);
        EntityRef ref = entity_manager_get_ref(entity_manager,i);

        if(e->kind == KIND_PLAYER){// do not save player
            continue;
        }

        if(e->kind == KIND_TILE){
            fwrite(&ref,sizeof(EntityRef),1,file);
            fwrite(e,sizeof(Entity),1,file);
        }
    }

    fclose(file);

    return 0; // success
}

int serialization_load_map(EngineState *engine_state, const char *file_name){

    Map *map = &engine_state->world_map;

    char buffer[200] = {0};
    sprintf(buffer,"%smaps/%s",RESOURCES_PATH,file_name);
    FILE* file = fopen(buffer, "rb");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    fread(&VERSION,sizeof(VERSION),1,file);

    //set map
    // clear map first
    map_clear_data(map);
    fread(map,sizeof(Map),1,file);

    // now iterate over ref and entity and put them inside the entity_manager

    // get it
    int tile_counter = 0;
    fread(&tile_counter,sizeof(tile_counter),1,file);
    if(tile_counter <= 0) return 1; // error

    SDL_Log("tile_counter:%i",tile_counter);

    // highest index counter
    int highest_idx = 0;

    for (int i = 0; i < tile_counter; ++i) {
        Entity e = {0};
        EntityRef ref = {0};

        fread(&ref,sizeof(EntityRef),1,file);
        fread(&e,sizeof(Entity),1,file);

        engine_state->entity_manager.entities[ref.idx] = e;
        engine_state->entity_manager.gen[ref.idx] = ref.gen;
        engine_state->entity_manager.used[ref.idx] = true;

        //get highest index
        highest_idx = (ref.idx > highest_idx)?ref.idx:highest_idx;

        engine_state->entity_manager.count++;
    }

    engine_state->entity_manager.highest_idx = highest_idx + 1;

    fclose(file);

    return 0;
}