/*
	Copyright (c) 2024 Piotr Stradowski. All rights reserved.
	Software distributed under the permissive MIT License.
*/

#pragma once
#include <SDL_surface.h>

class Level
{
public:
	~Level();

	void Init();
private:
	void LoadAssets();
	void DestroyAssets();
	
	void LoadLevel();

	SDL_Surface* whitePixelImage = nullptr;
};