/*
    Copyright (c) 2024 Piotr Stradowski. All rights reserved.
    Software distributed under the permissive MIT License.
*/

#include "ecs_entity.h"

static uint32 newEntityGlobalId = 0;

Entity::Entity(uint32 componentMask) : id(newEntityGlobalId++)
{
    this->componentMask = componentMask;
}
