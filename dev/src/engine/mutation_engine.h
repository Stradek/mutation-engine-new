/*
	Copyright (c) 2024 Piotr Stradowski. All rights reserved.
	Software distributed under the permissive MIT License.
*/

#pragma once

#include "renderer.h"
#include "ecs_manager.h"

class IEngineApplication;

class GameEngine
{
public:
	GameEngine(GameEngine& other) = delete;
	void operator=(GameEngine& other) = delete;

	GameEngine() = default;

	static void Run(IEngineApplication& appInstanceRef);

	void Close();
private:
	static GameEngine& GetInstance();
	static void DestroyInstance();

	void SetEngineApplication(IEngineApplication& appInstanceRef);

	void StartUp();
	void ShutDown();

	void Update();
	void RenderFrame();

	void _Run(IEngineApplication& appInstance);

	static GameEngine* m_instance;
	IEngineApplication* m_appInstance = nullptr;
	bool m_shutDown = false;

	Renderer m_renderer;
	EntityComponentSystemManager* m_entityComponentSystemManager;
};
