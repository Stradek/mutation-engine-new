/*
    Copyright (c) 2024 Piotr Stradowski. All rights reserved.
    Software distributed under the permissive MIT License.
*/

#include "mutation_engine.h"

#include "types.h"
#include "debug.h"
#include "renderer.h"
#include "utils.h"

#include <SDL2/SDL.h>

#include <math.h>
#include <stdio.h>

GameEngine* GameEngine::m_instance;

GameEngine::GameEngine() : m_appInstance(nullptr)
{
}

GameEngine& GameEngine::GetInstance()
{
    if (!m_instance)
    {
        m_instance = new GameEngine();
        // ENGINE_ASSERT(m_instance, "Failed to allocate engine instance.");
    }
    return *m_instance;
}

void GameEngine::DestroyInstance()
{
}

void GameEngine::Run(IEngineApplication& appInstance)
{
    // Core::Log::Init();

    {
        GameEngine& engineInstance = GameEngine::GetInstance();
        engineInstance.EngineRun(appInstance);
    }

    GameEngine::DestroyInstance();
    // Core::Log::Close();
}

void GameEngine::StartUp()
{
    ENGINE_INFO("Hello! It's Mutation Engine!\n");

    bool isRendererInitialized = InitRenderer() == 0;
    // ASSERT(isRendererInitialized, "Initializing renderer failed.");
}

void GameEngine::EngineRun(IEngineApplication& appInstance)
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
            RendererOptions rendererOptions = GetRendererOptions();
            const float timeUntilTargetFrameTime = fmax(0.0f, rendererOptions.targetFrameTime - elapsedFrameTime);
            SDL_Delay(floor(timeUntilTargetFrameTime));
        }
    }

    ShutDown();
}

void GameEngine::SetEngineApplication(IEngineApplication& appInstance)
{
    m_appInstance = &appInstance;
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
}

void GameEngine::RenderFrame()
{
    RenderFrame();
}

void GameEngine::Close()
{
    m_shutDown = true;
}

void GameEngine::ShutDown()
{
    bool isRendererSuccessfullyClosed = CloseRenderer() == 0;
    // ASSERT(isRendererSuccessfullyClosed, "Initializing renderer failed.");
}
