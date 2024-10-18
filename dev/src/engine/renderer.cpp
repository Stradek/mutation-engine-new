#include "renderer.h"

#include "utils.h"
#include "debug.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_log.h>


RendererOptions rendererOptions
{
    -1, // set in cpp in init_renderer_options()
    60
};

RendererOptions Renderer::GetRendererOptions()
{
    return rendererOptions;
}

void Renderer::InitSDL() 
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0) 
    {
        ENGINE_CRITICAL("Unable to initialize SDL: %s", SDL_GetError());
    }

    window = SDL_CreateWindow("Mutation Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, 0);
    if (window == NULL) 
    {
        ENGINE_CRITICAL("Unable to create window: %s", SDL_GetError());
        SDL_Quit();
    }

    sdlRenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (sdlRenderer == NULL) 
    {
        SDL_DestroyWindow(window);
        ENGINE_CRITICAL("Unable to create renderer: %s", SDL_GetError());
        SDL_Quit();
    }

    screenSurface = SDL_GetWindowSurface(window);
}

void Renderer::CloseSDL()
{
    if (sdlRenderer != NULL)
    {
        SDL_DestroyRenderer(sdlRenderer);
    }

    if (window != NULL)
    {
        SDL_DestroyWindow(window);
    }

    SDL_Quit();
}


void Renderer::InitRendererOptions()
{
    rendererOptions.targetFrameTime = (float)SECONDS_TO_MILLISECONDS / rendererOptions.targetFPS;
}

void Renderer::RenderFrame()
{
    SDL_SetRenderDrawColor(sdlRenderer, 94, 25, 20, 255);
    SDL_RenderClear(sdlRenderer);

    SDL_RenderPresent(sdlRenderer);
}

Renderer::Renderer() : window(nullptr), sdlRenderer(nullptr)
{
}

void Renderer::StartUp()
{
    InitRendererOptions();

    InitSDL();
}

void Renderer::ShutDown()
{
    CloseSDL();
}
