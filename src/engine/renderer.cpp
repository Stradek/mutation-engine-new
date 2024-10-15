#include "renderer.h"

#include "utils.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_log.h>


RendererOptions rendererOptions
{
    -1, // set in cpp in init_renderer_options()
    60
};

RendererOptions GetRendererOptions()
{
    return rendererOptions;
}

/************************* SDL *************************/

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;

int InitSDL() 
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0) 
    {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        return 1;
    }

    window = SDL_CreateWindow("Mutation Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, 0);
    if (window == NULL) 
    {
        SDL_Log("Unable to create window: %s", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) 
    {
        SDL_DestroyWindow(window);
        SDL_Log("Unable to create renderer: %s", SDL_GetError());
        SDL_Quit();
        return 1;
    }
    return 0;
}

int CloseSDL() 
{
    if (renderer != NULL)
    {
        SDL_DestroyRenderer(renderer);
    }

    if (window != NULL)
    {
        SDL_DestroyWindow(window);
    }

    SDL_Quit();
    return 0;
}

/************************* Renderer *************************/

void InitRendererOptions()
{
    rendererOptions.targetFrameTime = (float)SECONDS_TO_MILLISECONDS / rendererOptions.targetFPS;
}

int InitRenderer()
{
    InitRendererOptions();

    if (InitSDL() != 0)
    {
        SDL_LogCritical(SDL_LOG_CATEGORY_ERROR, "Failed to initialize SDL");
        return 1;
    }

    return 0;
}

int RenderFrame()
{
    SDL_SetRenderDrawColor(renderer, 94, 25, 20, 255);
    SDL_RenderClear(renderer);

    SDL_RenderPresent(renderer);
    return 0;
}

int CloseRenderer()
{
    if (CloseSDL() != 0)
    {
        SDL_LogCritical(SDL_LOG_CATEGORY_ERROR, "Failed to close SDL");
        return 1;
    }

    return 0;
}

