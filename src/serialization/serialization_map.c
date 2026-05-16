#include "serialization_map.h"


static int VERSION = 1;

int serialization_save_map(Map *map, EngineState *engine_state, const char *file_name)
{
    // PUBLIC RESOURCES_PATH

    // std::string path = RESOURCES_PATH "maps/";

    char buffer[200] = {0};
    sprintf(buffer,"%s%s",RESOURCES_PATH,file_name);
    FILE* file = fopen(buffer, "wb");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    fwrite(&VERSION,sizeof(VERSION),1,file);

    fwrite(&map,sizeof(map),1,file);

    fclose(file);

    return 0; // success
}
