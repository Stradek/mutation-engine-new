#include "mutation_engine.h"

#include "common/types.h"
#include "common/debug.h"
#include "renderer.h"
#include "utils.h"

#include <SDL2/SDL.h>

#include <math.h>
#include <stdio.h>

int mutation_engine_init(void) 
{
    ENGINE_INFO("Hello! It's Mutation Engine!\n");
    if (init_renderer() != 0)
    {
        return 1;
    }

    return 0;
}

int mutation_engine_run_loop(void) 
{
    bool running = true;
    size_t fpsCounter = 0;
    uint64 lastPerformanceLoggingTime = SDL_GetPerformanceCounter();

    while (running)
    {
        const uint64 frameTimeStart = SDL_GetPerformanceCounter();
        {
            const float lastPerformanceLoggingDeltaTime = (frameTimeStart - lastPerformanceLoggingTime) / (float) SDL_GetPerformanceFrequency() * SECONDS_TO_MILLISECONDS;
            if (lastPerformanceLoggingDeltaTime >= 1000)
            {
                ENGINE_DEBUG("FPS: %zd\n", fpsCounter);
                lastPerformanceLoggingTime = SDL_GetPerformanceCounter();
                fpsCounter = 0;
            }
        }

        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                running = false;
            }
            else if (event.type == SDL_KEYDOWN)
            {
                if (event.key.keysym.sym == SDLK_ESCAPE)
                {
                    running = false;
                }
            }
        }

        render_frame();

        {
            ++fpsCounter;
            const uint64 frameTimeEnd = SDL_GetPerformanceCounter();

            const float elapsedFrameTime = (frameTimeEnd - frameTimeStart) / (float) SDL_GetPerformanceFrequency() * SECONDS_TO_MILLISECONDS;
            const float timeUntilTargetFrameTime = fmax(0.0f, rendererOptions.targetFrameTime - elapsedFrameTime);
            SDL_Delay(floor(timeUntilTargetFrameTime));
        }
    }
    return 0;
}

int mutation_engine_close(void)
{
    if (close_renderer() != 0)
    {
        return 1;
    }

    return 0;
}
