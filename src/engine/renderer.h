#pragma once

#include "common/types.h"

/************************* Renderer Settings *************************/

typedef struct 
{
    float targetFrameTime;
    uint8 targetFPS;
} RendererOptions;

extern RendererOptions rendererOptions;

/************************* SDL *************************/

int init_sdl(void);
int close_sdl(void);

/************************* Renderer *************************/

int init_renderer(void);
int render_frame(void);
int close_renderer(void);
