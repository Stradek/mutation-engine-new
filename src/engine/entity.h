#pragma once

#include "common/types.h"

typedef struct Entity
{
    uint32 id;
    uint32 componentMask;
} Entity;


void addEntity(struct Entity *entity);
