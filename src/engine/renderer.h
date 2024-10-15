#pragma once

#include "types.h"

/************************* Renderer Settings *************************/

struct RendererOptions
{
    float targetFrameTime;
    uint8 targetFPS;
};

/************************* SDL *************************/

int init_sdl();
int close_sdl();

/************************* Renderer *************************/

RendererOptions get_renderer_options();

int init_renderer();
int render_frame();
int close_renderer();
