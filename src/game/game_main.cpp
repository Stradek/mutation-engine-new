/*
    Copyright (c) 2024 Piotr Stradowski. All rights reserved.
    Software distributed under the permissive MIT License.
*/

#include "common/debug.h"
#include "engine/mutation_engine.h"
#include "game.h"

int main(int argc, char* argv[])
{
    GAME_INFO("Hello! It's Pong Game!\n");

    {
        IEngineApplication* gameInstance = new Game();
        GameEngine::Run(*gameInstance);
    }
}
