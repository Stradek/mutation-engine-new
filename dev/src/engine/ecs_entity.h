/*
	Copyright (c) 2024 Piotr Stradowski. All rights reserved.
	Software distributed under the permissive MIT License.
*/

#pragma once

#include "system.h"
#include "types.h"

#include <vector>
#include <memory>


struct Entity
{
    Entity(uint32 componentMask);

    template<typename Component>
    void AddComponent()
    {
        uint32 componentBit = GetECSComponentBit<Component>();
        componentMask |= componentBit;

        EntityComponentSystemManager* ecsManager = EntityComponentSystemManager::GetInstance();
        ecsManager->RegisterComponent<Component>(*this);
    }

    const uint32 id;
    uint32 componentMask;
};