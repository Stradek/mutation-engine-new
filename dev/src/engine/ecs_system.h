/*
	Copyright (c) 2024 Piotr Stradowski. All rights reserved.
	Software distributed under the permissive MIT License.
*/

#pragma once

#include <ecs_entity.h>

template<typename Derived>
class ECSSystem
{
public:
	static void Update()
	{
		return Derived::Update();
	}
	static bool IsEntityValidForSystem(Entity& entity)
	{
		return Derived::IsEntityValidForSystem(entity);
	}

protected:
	static bool IsComponentMasksMatch(uint32 mask_a, uint32 mask_b)
	{
		if ((mask_a & mask_b) == mask_a)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
};

class SpriteRenderingSystem : public ECSSystem<SpriteRenderingSystem>
{
public:
	static bool IsEntityValidForSystem(Entity& entity);
	
	static void Update(Entity& entity);
};

class MovementSystem : public ECSSystem<MovementSystem>
{
public:
	static bool IsEntityValidForSystem(Entity& entity);

	static void Update(Entity& entity);

	static void SetPosition(Entity& entity, float x, float y);
};