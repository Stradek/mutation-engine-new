/*
	Copyright (c) 2024 Piotr Stradowski. All rights reserved.
	Software distributed under the permissive MIT License.
*/

#pragma once

#include "system.h"
#include "ecs_entity.h"
#include "ecs_component.h"

#include <memory>
#include <vector>

#define MAX_ENTITY_COUNT 256

class EntityComponentSystemManager : ISystem
{
public:
	EntityComponentSystemManager(EntityComponentSystemManager& entityComponentSystemManager) = delete;
	void operator=(EntityComponentSystemManager& entityComponentSystemManager) = delete;

	EntityComponentSystemManager() = default;

	static EntityComponentSystemManager* GetInstance();

	void StartUp() override;
	void ShutDown() override;

	void Update() override;

	Entity& AddEntity();

	template<typename Component>
	void RegisterComponent(Entity& entity)
	{
		if (typeid(Component) == typeid(TransformComponent))
		{
			TransformComponent& componentItem = m_transformComponentList[entity.id];
			componentItem = TransformComponent();
		}
		else if (typeid(Component) == typeid(SpriteRenderingComponent))
		{
			SpriteRenderingComponent& componentItem = m_spriteRenderingComponentList[entity.id];
			componentItem = SpriteRenderingComponent();
		}
	}

	template<typename Component>
	Component& FindComponent(Entity& entity)
	{
		if constexpr (std::is_same_v<Component, TransformComponent>)
		{
			return m_transformComponentList[entity.id];
		}
		else if constexpr (std::is_same_v<Component, SpriteRenderingComponent>)
		{
			return m_spriteRenderingComponentList[entity.id];
		}
	}

private:
	std::vector<std::shared_ptr<Entity>> m_entityList;
	TransformComponent m_transformComponentList[MAX_ENTITY_COUNT];
	SpriteRenderingComponent m_spriteRenderingComponentList[MAX_ENTITY_COUNT];
	
	static EntityComponentSystemManager* m_instance;
};