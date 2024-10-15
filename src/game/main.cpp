#include "common/debug.h"
#include "engine/mutation_engine.h"

int main(int argc, char **argv)
{
    GAME_INFO("Hello! It's Pong Game!\n");

    if (mutation_engine_init() != 0)
    {
        return 1;
    }

    mutation_engine_run_loop();
    mutation_engine_close();
}

