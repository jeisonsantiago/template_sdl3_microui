#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

#include "entity.h"
#include "ecs.h"

typedef struct{
    Entity          entities[MAX_ENTITIES];
    uint32_t        count;

    bool            used[MAX_ENTITIES];
    uint32_t        gen[MAX_ENTITIES];

}EntityManager;

void entity_manager_init(EntityManager *self);
EntityRef entity_manager_add(EntityManager *self, Kind kind);
EntityRef entity_manager_get_ref(EntityManager *self,uint32_t idx);
Entity *entity_manager_get(EntityManager *self, EntityRef ref);
Entity *entity_manager_get_by_index(EntityManager *self, uint32_t idx);
void entity_manager_remove(EntityManager *self, EntityRef ref);
void entity_manager_clear(EntityManager *self);
EntityRef null_entity();




#endif // ENTITY_MANAGER_H
