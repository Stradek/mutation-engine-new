/*
	Copyright (c) 2024 Piotr Stradowski. All rights reserved.
	Software distributed under the permissive MIT License.
*/

#pragma once

#include "engine_application.h"
#include "level.h"

class Game : public IEngineApplication
{
public:
	Game() = default;
	Game(Game& game) = delete;
	~Game() = default;

	void StartUp() override;
	void Update() override;
	void ShutDown() override;

private:
	Level level;
};