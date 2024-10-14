#pragma once

#include "types.h"

#include <stdio.h>

#ifdef _WIN32
#include <windows.h>
#endif

/************************* ASSERT *************************/

// TODO: might separate to ASSERT and FATAL_ASSERT in the future

// assert macro
#ifdef DEBUG
#define ASSERT(condition, message) \
    if (!(condition)) \
    { \
        fprintf(stderr, "Assertion failed: (%s), function %s, file %s, line %d\nMessage: %s\n", #condition, __FUNCTION__, __FILE__, __LINE__, message); \
        abort(); \
    }
#else
#define ASSERT(condition, message)
#endif

/************************* LOGGING *************************/

// engine logging macros
#ifdef DEBUG
#define ENGINE_DEBUG(message, ...) \
    fprintf(stdout, "[ENGINE] [DEBUG] " message, ##__VA_ARGS__)
#define ENGINE_INFO(message, ...) \
    fprintf(stdout, "[ENGINE] [INFO] " message, ##__VA_ARGS__)
#define ENGINE_WARN(message, ...) \
    fprintf(stdout, "[ENGINE] [WARN] " message, ##__VA_ARGS__)
#define ENGINE_ERROR(message, ...) \
    fprintf(stderr, "[ENGINE] [ERROR] " message, ##__VA_ARGS__)
#define ENGINE_CRITICAL(message, ...) \
    fprintf(stderr, "[ENGINE] [CRITICAL] " message, ##__VA_ARGS__)
#else
#define ENGINE_DEBUG(message, ...)
#define ENGINE_INFO(message, ...)
#define ENGINE_WARN(message, ...)
#define ENGINE_ERROR(message, ...)
#define ENGINE_CRITICAL(message, ...)
#endif

// game logging macros
#ifdef DEBUG
#define GAME_DEBUG(message, ...) \
    fprintf(stdout, "[GAME] [DEBUG] " message, ##__VA_ARGS__)
#define GAME_INFO(message, ...) \
    fprintf(stdout, "[GAME] [INFO] " message, ##__VA_ARGS__)
#define GAME_WARN(message, ...) \
    fprintf(stdout, "[GAME] [WARN] " message, ##__VA_ARGS__)
#define GAME_ERROR(message, ...) \
    fprintf(stderr, "[GAME] [ERROR] " message, ##__VA_ARGS__)
#define GAME_CRITICAL(message, ...) \
    fprintf(stderr, "[GAME] [CRITICAL] " message, ##__VA_ARGS__)
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
#ifdef DEBUG
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
