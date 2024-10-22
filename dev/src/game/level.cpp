/*
	Copyright (c) 2024 Piotr Stradowski. All rights reserved.
	Software distributed under the permissive MIT License.
*/

#pragma once

#include "level.h"
#include "debug.h"

#include <SDL_filesystem.h>
#include <SDL_image.h>

#include <filesystem>
#include <ecs_manager.h>

std::filesystem::path GetResourcePath(const char* resourcePath)
{
	std::filesystem::path basePath = SDL_GetBasePath();
	std::filesystem::path resourceFullPath = basePath / ".." / ".." / "dev" / "resources" / resourcePath;

	return resourceFullPath;
}

void Level::Init()
{
	LoadAssets();

	LoadLevel();
}

void Level::LoadAssets()
{
	std::filesystem::path whitePixelPath = GetResourcePath("white_pixel.png");
	whitePixelImage = IMG_Load(whitePixelPath.string().c_str());
	if (whitePixelImage == nullptr)
	{
		GAME_ERROR("Unable to load image %s! SDL Error: %s\n", whitePixelPath.string().c_str(), SDL_GetError());
	}
}

Level::~Level()
{
	DestroyAssets();
}

void Level::DestroyAssets()
{
	SDL_FreeSurface(whitePixelImage);
	whitePixelImage = nullptr;
}

void Level::LoadLevel()
{
	EntityComponentSystemManager* ecsManager = EntityComponentSystemManager::GetInstance();
	Entity& entity = ecsManager->AddEntity();
	entity.AddComponent<TransformComponent>();
	entity.AddComponent<SpriteRenderingComponent>();
}
