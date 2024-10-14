# Coding Style Guide

## File Naming
- Use `snake_case` for file names for following file types:
    - Source Files
    - Header Files
    - Script Files
    - Configuration Files
- Use `UPPER_SNAKE_CASE` for .md file names.
- Example: `mutation_engine.c`, `common_types.h`

## Include Guards
- Use `#pragma once` for include guards.

## Header Files
- Include header files in the following order with empty line between each
    section:
    1. Corresponding Header to Project Source File
    2. Project Headers
    3. Third Party Library Headers
    4. Standard Library Headers

- Example:
```c
// mutation_engine.c 
#include "mutation_engine.h"

#include "common/common_types.h"
#include "renderer.h"

#include <SDL2/SDL.h>

#include <stdio.h>
```

## Variable Naming
- Use `camelCase` for variable names.
- Example: `framesPerSecondCounter`, `lastPerformanceLoggingTime`

## Function Naming
- Use `snake_case` for function names.
- Example: `mutation_engine_init()`, `render_frame()`

## Type Naming
- Use `PascalCase` for custom types.
- Example: `RendererOptions`, `StaticMeshComponent`

## Enumerations
- Use `UPPER_SNAKE_CASE` for enumerations.
- Example: `TRANSFORM_COMPONENT_`, `RendererType`

## Constants
- Use `UPPER_SNAKE_CASE` for constants.
- Example: `SECONDS_TO_MILLISECONDS`, `WINDOW_WIDTH`

## Macros
- Use `UPPER_SNAKE_CASE` for macros.
- Example: `#define MAX(a, b) ((a) > (b) ? (a) : (b))`

## Spacing
- Use spaces around control flow statements and within parentheses between the
    operator and the operands.
- Example: `while (running)`, `if (event.type == SDL_QUIT)`

## Indentation
- Use 4 spaces for indentation.
- Example:
``` c
int close_sdl(void) 
{
    if (renderer != NULL)
    {
        SDL_DestroyRenderer(renderer);
    }

    if (window != NULL)
    {
        SDL_DestroyWindow(window);
    }

    SDL_Quit();
    return 0;
} 
```

## Brace Style
- Use the Allman style for braces.
- Example:
```c
int close_sdl(void) 
{
    if (renderer != NULL)
    {
        SDL_DestroyRenderer(renderer);
    }

    if (window != NULL)
    {
        SDL_DestroyWindow(window);
    }

    SDL_Quit();
    return 0;
}
```

## Comments
- Use multi-line comments in one line with the section name centered and 25 stars on both sides (50 stars total, like on the flag of the United States of America) for readability.
- Example:
```c 
/************************* Renderer Settings *************************/
```
