/*
	Copyright (c) 2024 Piotr Stradowski. All rights reserved.
	Software distributed under the permissive MIT License.
*/

#pragma once

#include "engine/engine_application.h"

class Game : public IEngineApplication
{
public:
	void StartUp() override;
	void Update() override;
	void ShutDown() override;
};