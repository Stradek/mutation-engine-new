#include "renderer.h"

#include "utils.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_log.h>


RendererOptions rendererOptions
{
    -1, // set in cpp in init_renderer_options()
    60
};

RendererOptions get_renderer_options()
{
    return rendererOptions;
}

/************************* SDL *************************/

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;

int init_sdl() 
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

int close_sdl() 
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

void init_renderer_options()
{
    rendererOptions.targetFrameTime = (float)SECONDS_TO_MILLISECONDS / rendererOptions.targetFPS;
}

int init_renderer()
{
    init_renderer_options();

    if (init_sdl() != 0)
    {
        SDL_LogCritical(SDL_LOG_CATEGORY_ERROR, "Failed to initialize SDL");
        return 1;
    }

    return 0;
}

int render_frame()
{
    SDL_SetRenderDrawColor(renderer, 94, 25, 20, 255);
    SDL_RenderClear(renderer);

    SDL_RenderPresent(renderer);
    return 0;
}

int close_renderer()
{
    if (close_sdl() != 0)
    {
        SDL_LogCritical(SDL_LOG_CATEGORY_ERROR, "Failed to close SDL");
        return 1;
    }

    return 0;
}

