#include "ecs_system.h"

#include "ecs_component.h"
#include <ecs_manager.h>

void SpriteRenderingSystem::Update(Entity& entity)
{
	if (SpriteRenderingSystem::IsEntityValidForSystem(entity))
	{

	}
}

bool SpriteRenderingSystem::IsEntityValidForSystem(Entity& entity)
{
	uint32 systemDependencyMask = GetECSComponentBit<TransformComponent>() & GetECSComponentBit<SpriteRenderingComponent>();

	return IsComponentMasksMatch(entity.componentMask, systemDependencyMask);
}

void MovementSystem::Update(Entity& entity)
{

}

bool MovementSystem::IsEntityValidForSystem(Entity& entity)
{
	uint32 systemDependencyMask = GetECSComponentBit<TransformComponent>();

	return IsComponentMasksMatch(entity.componentMask, systemDependencyMask);
}

void MovementSystem::SetPosition(Entity& entity, float x, float y)
{
	EntityComponentSystemManager* ecsManager = EntityComponentSystemManager::GetInstance();
	TransformComponent& transformComponent = ecsManager->FindComponent<TransformComponent>(entity);

	transformComponent.x = x;
	transformComponent.y = y;
}
