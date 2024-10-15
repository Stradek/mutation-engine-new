/*
	Copyright (c) 2024 Piotr Stradowski. All rights reserved.
	Software distributed under the permissive MIT License.
*/

#pragma once

#include "system.h"
#include "types.h"

#include <SDL2/SDL_video.h>
#include <SDL2/SDL_render.h>

struct RendererOptions
{
    float targetFrameTime;
    uint8 targetFPS;
};


class Renderer : ISystem
{
public:
	Renderer();

	// Inherited via ISystem
	void StartUp() override;
	void ShutDown() override;

	void InitSDL();
	void CloseSDL();

	void InitRendererOptions();
	static RendererOptions GetRendererOptions();

	void RenderFrame();
private:
	SDL_Window* window;
	SDL_Renderer* sdlRenderer;
};
