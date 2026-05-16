#include "entity.h"


bool entity_valid(Entity *self)
{
    return self->kind != KIND_NIL;
}

bool entity_ref_valid(EntityRef ref){
    return (ref.gen != 0 && ref.idx > 0);
}

EntityRef invalid_entity_ref()
{
    return (EntityRef){0,0};
}
