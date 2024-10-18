#include "renderer.h"

#include "utils.h"
#include "debug.h"

#include <SDL.h>
#include <SDL_log.h>
#include <SDL_image.h>


RendererOptions rendererConfiguration
{
    -1, // set in cpp in init_renderer_options()
    60
};

RendererOptions Renderer::GetRendererConfiguration()
{
    return rendererConfiguration;
}

void Renderer::InitSDL() 
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0) 
    {
        ENGINE_CRITICAL("Unable to initialize SDL: %s", SDL_GetError());
    }

    if (IMG_Init(IMG_INIT_PNG) == 0)
    {
        ENGINE_CRITICAL("Failed to initialize SDL_image: ", IMG_GetError());
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
        sdlRenderer = nullptr;
    }

    if (window != NULL)
    {
        SDL_DestroyWindow(window);
        window = nullptr;
    }

    IMG_Quit();

    SDL_Quit();
}


void Renderer::InitRendererConfiguration()
{
    rendererConfiguration.targetFrameTime = (float)SECONDS_TO_MILLISECONDS / rendererConfiguration.targetFPS;
}

void Renderer::RenderFrame()
{
    SDL_SetRenderDrawColor(sdlRenderer, 94, 25, 20, 255);
    SDL_RenderClear(sdlRenderer);

    SDL_RenderPresent(sdlRenderer);
}

Renderer::Renderer()
{
}

void Renderer::StartUp()
{
    InitRendererConfiguration();

    InitSDL();
}

void Renderer::ShutDown()
{
    CloseSDL();
}
