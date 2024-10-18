/*
	Copyright (c) 2024 Piotr Stradowski. All rights reserved.
	Software distributed under the permissive MIT License.
*/

#pragma once

#include "renderer.h"

class IEngineApplication;

class GameEngine
{
public:
	GameEngine(GameEngine& m_gameEngine) = delete;
	void operator=(GameEngine& m_gameEngine) = delete;

	static void Run(IEngineApplication& appInstanceRef);

	void Close();
private:
	GameEngine() {};
	virtual ~GameEngine() {};

	static GameEngine& GetInstance();
	static void DestroyInstance();

	void SetEngineApplication(IEngineApplication& appInstanceRef);

	void StartUp();
	void ShutDown();

	void Update();
	void RenderFrame();

	void EngineRun(IEngineApplication& appInstance);

	static GameEngine* m_instance;
	IEngineApplication* m_appInstance = nullptr;
	bool m_shutDown = false;

	Renderer m_renderer;
};
