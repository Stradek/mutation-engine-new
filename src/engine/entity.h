#pragma once

#include "common/types.h"

struct Entity
{
    uint32 id;
    uint32 componentMask;
};

void addEntity(struct Entity *entity);
