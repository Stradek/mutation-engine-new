/*
	Copyright (c) 2024 Piotr Stradowski. All rights reserved.
	Software distributed under the permissive MIT License.
*/

#pragma once

#include "system.h"
#include "types.h"

#include <SDL_video.h>
#include <SDL_render.h>

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

	static RendererOptions GetRendererConfiguration();

	void RenderFrame();
private:
	void InitSDL();
	void CloseSDL();

	void InitRendererConfiguration();

	SDL_Window* window = nullptr;
	SDL_Renderer* sdlRenderer = nullptr;
	SDL_Surface* screenSurface = nullptr;
};
