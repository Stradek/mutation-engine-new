/*
	Copyright (c) 2024 Piotr Stradowski. All rights reserved.
	Software distributed under the permissive MIT License.
*/

#pragma once

#include "system.h"
#include "types.h"
#include "debug.h"

#include <unordered_map>
#include <SDL_surface.h>

const uint8 INVALID_COMPONENT_BIT = 0x00;
const uint8 TRANSFORM_COMPONENT_BIT = 0x01 << 0;
const uint8 SPRITE_RENDERING_COMPONENT_BIT = 0x01 << 1;

struct TransformComponent
{
	float x, y;
};

struct SpriteRenderingComponent
{
	SDL_Surface* surface;
};

template<typename Component>
uint8 GetECSComponentBit()
{
	static std::unordered_map<size_t, uint8> componentBitMap = {
		{ typeid(TransformComponent).hash_code(), TRANSFORM_COMPONENT_BIT },
		{ typeid(SpriteRenderingComponent).hash_code(), SPRITE_RENDERING_COMPONENT_BIT }
	};

	const size_t componentType = typeid(Component).hash_code();
	auto it = componentBitMap.find(componentType);

	if (it != componentBitMap.end())
	{
		return it->second;
	}
	else
	{
		ENGINE_CRITICAL("Component '%s' not defined. Can't assign bit to undefined component.", typeid(Component).name());
		return INVALID_COMPONENT_BIT;
	}
}