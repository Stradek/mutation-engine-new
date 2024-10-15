/*
	Copyright (c) 2024 Piotr Stradowski. All rights reserved.
	Software distributed under the permissive MIT License.
*/

#pragma once

#include "types.h"

struct RendererOptions
{
    float targetFrameTime;
    uint8 targetFPS;
};

int InitSDL();
int CloseSDL();

/************************* Renderer *************************/

RendererOptions GetRendererOptions();

int InitRenderer();
int RenderFrame();
int CloseRenderer();
