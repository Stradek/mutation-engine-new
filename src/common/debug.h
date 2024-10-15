#pragma once

#include "types.h"

#include <stdio.h>

#ifdef _WIN32
#include <windows.h>
#endif

/************************* ASSERT *************************/

// TODO: might separate to ASSERT and FATAL_ASSERT in the future

// assert macro
#ifdef BUILD_DEBUG
#define ASSERT(condition, message) \
    if (!(condition)) \
    { \
        std::cerr << "Assertion failed: (" << #condition << "), function " << __func__  << " , file " << __FILE__ << ", line " << __LINE__ << "\nMessage: " << message << "\n"; \
        abort(); \
    }
#else
#define ASSERT(condition, message)
#endif

/************************* LOGGING *************************/

// engine logging macros
#ifdef BUILD_DEBUG
#define ENGINE_DEBUG(message, ...) \
    printf("[ENGINE] [DEBUG] " message "\n", ##__VA_ARGS__)
#define ENGINE_INFO(message, ...) \
    printf("[ENGINE] [INFO] " message "\n", ##__VA_ARGS__)
#define ENGINE_WARN(message, ...) \
    printf("[ENGINE] [WARN] " message "\n", ##__VA_ARGS__)
#define ENGINE_ERROR(message, ...) \
    printf("[ENGINE] [ERROR] " message "\n", ##__VA_ARGS__)
#define ENGINE_CRITICAL(message, ...) \
    printf("[ENGINE] [CRITICAL] " message "\n", ##__VA_ARGS__)
#else
#define ENGINE_DEBUG(message, ...)
#define ENGINE_INFO(message, ...)
#define ENGINE_WARN(message, ...)
#define ENGINE_ERROR(message, ...)
#define ENGINE_CRITICAL(message, ...)
#endif

// game logging macros
#ifdef BUILD_DEBUG
#define GAME_DEBUG(message, ...) \
    printf("[GAME] [DEBUG] " message "\n", ##__VA_ARGS__)
#define GAME_INFO(message, ...) \
    printf("[GAME] [INFO] " message "\n", ##__VA_ARGS__)
#define GAME_WARN(message, ...) \
    printf("[GAME] [WARN] " message "\n", ##__VA_ARGS__)
#define GAME_ERROR(message, ...) \
    printf("[GAME] [ERROR] " message "\n", ##__VA_ARGS__)
#define GAME_CRITICAL(message, ...) \
    printf("[GAME] [CRITICAL] " message "\n", ##__VA_ARGS__)
#else
#define GAME_DEBUG(message, ...)
#define GAME_INFO(message, ...)
#define GAME_WARN(message, ...)
#define GAME_ERROR(message, ...)
#define GAME_CRITICAL(message, ...)
#endif

/************************* DEBUG BREAK *************************/

bool is_debugger_attached(void);

// debug break macro
#ifdef BUILD_DEBUG
#define DEBUG_BREAK() \
    if (is_debugger_attached()) \
    { \
        __debugbreak(); \
    } \
    else \
    { \
        ENGINE_WARN("Debugger is not attached, press Enter to continue...\n"); \
        getchar(); \
    }
#else
#define DEBUG_BREAK()
#endif
