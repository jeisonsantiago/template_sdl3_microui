#include "entity.h"


bool entity_valid(Entity *self)
{
    return self->kind != KIND_NIL;
}
