/*
    Copyright (c) 2024 Piotr Stradowski. All rights reserved.
    Software distributed under the permissive MIT License.
*/

#include "mutation_engine.h"

#include "engine_application.h"
#include "types.h"
#include "debug.h"
#include "utils.h"

#include <SDL.h>

#include <math.h>
#include <stdio.h>

GameEngine* GameEngine::m_instance = nullptr;

GameEngine& GameEngine::GetInstance()
{
    if (!m_instance)
    {
        m_instance = new GameEngine();
    }
    return *m_instance;
}

void GameEngine::DestroyInstance()
{
    ASSERT(m_instance, "Game engine instance was called to be destroyed but it's not initialized.");

    delete m_instance;
    m_instance = nullptr;
}

void GameEngine::Run(IEngineApplication& appInstance)
{
    // Core::Log::Init();

    {
        GameEngine& engineInstance = GameEngine::GetInstance();
        engineInstance._Run(appInstance);
    }

    GameEngine::DestroyInstance();
    // Core::Log::Close();
}


void GameEngine::SetEngineApplication(IEngineApplication& appInstance)
{
    m_appInstance = &appInstance;
}

void GameEngine::StartUp()
{
    ENGINE_INFO("Hello! It's Mutation Engine!\n");

    m_renderer.StartUp();

    m_entityComponentSystemManager = EntityComponentSystemManager::GetInstance();
    m_entityComponentSystemManager->StartUp();

    m_appInstance->StartUp();
}

void GameEngine::_Run(IEngineApplication& appInstance)
{
    SetEngineApplication(appInstance);

    StartUp();

    size_t fpsCounter = 0;
    uint64 lastPerformanceLoggingTime = SDL_GetPerformanceCounter();
    while (!m_shutDown)
    {
        const uint64 frameTimeStart = SDL_GetPerformanceCounter();
        {
            const float lastPerformanceLoggingDeltaTime = (frameTimeStart - lastPerformanceLoggingTime) / (float)SDL_GetPerformanceFrequency() * SECONDS_TO_MILLISECONDS;
            if (lastPerformanceLoggingDeltaTime >= 1000)
            {
                ENGINE_DEBUG("FPS: %zd\n", fpsCounter);
                lastPerformanceLoggingTime = SDL_GetPerformanceCounter();
                fpsCounter = 0;
            }
        }

        Update();
        RenderFrame();

        {
            ++fpsCounter;
            const uint64 frameTimeEnd = SDL_GetPerformanceCounter();

            const float elapsedFrameTime = (frameTimeEnd - frameTimeStart) / (float)SDL_GetPerformanceFrequency() * SECONDS_TO_MILLISECONDS;
            RendererOptions rendererOptions = Renderer::GetRendererConfiguration();
            const float timeUntilTargetFrameTime = fmax(0.0f, rendererOptions.targetFrameTime - elapsedFrameTime);
            SDL_Delay(floor(timeUntilTargetFrameTime));
        }
    }

    ShutDown();
}

void GameEngine::Update()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
        {
            m_shutDown = true;
        }
        else if (event.type == SDL_KEYDOWN)
        {
            if (event.key.keysym.sym == SDLK_ESCAPE)
            {
                m_shutDown = true;
            }
        }
    }

    m_entityComponentSystemManager->Update();
    m_appInstance->Update();
}

void GameEngine::RenderFrame()
{
    m_renderer.RenderFrame();
}

void GameEngine::Close()
{
    m_shutDown = true;
}

void GameEngine::ShutDown()
{
    m_appInstance->ShutDown();

    m_entityComponentSystemManager->ShutDown();
    m_renderer.ShutDown();
}
