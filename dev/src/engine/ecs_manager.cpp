#include "ecs_manager.h"

#include "ecs_system.h"

EntityComponentSystemManager* EntityComponentSystemManager::m_instance = nullptr;

EntityComponentSystemManager* EntityComponentSystemManager::GetInstance()
{
	if (!m_instance)
	{
		m_instance = new EntityComponentSystemManager();
	}
	return m_instance;
}

void EntityComponentSystemManager::StartUp()
{
	m_entityList = std::vector<std::shared_ptr<Entity>>();
}

void EntityComponentSystemManager::ShutDown()
{
	m_entityList.clear();
}

void EntityComponentSystemManager::Update()
{
	for (std::shared_ptr<Entity> entity : m_entityList)
	{
		SpriteRenderingSystem::Update(*entity);
	}
}

Entity& EntityComponentSystemManager::AddEntity()
{
	std::shared_ptr<Entity> entity = std::make_shared<Entity>(0x00);
	m_entityList.push_back(entity);
	return *entity;
}