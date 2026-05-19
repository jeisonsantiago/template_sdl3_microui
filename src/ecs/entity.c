#include "entity.h"


bool entity_valid(Entity *self)
{
    return (self->kind != KIND_NIL) ;
}

bool entity_ref_valid(EntityRef ref){
    return (ref.idx != INVALID_IDX);
}

EntityRef invalid_entity_ref()
{
    return (EntityRef){INVALID_IDX,INVALID_IDX};
}
