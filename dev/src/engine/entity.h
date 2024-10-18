/*
	Copyright (c) 2024 Piotr Stradowski. All rights reserved.
	Software distributed under the permissive MIT License.
*/

#pragma once

#include "types.h"

struct Entity
{
    uint32 id;
    uint32 componentMask;
};

void AddEntity(struct Entity *entity);
