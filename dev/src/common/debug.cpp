/*
    Copyright (c) 2024 Piotr Stradowski. All rights reserved.
    Software distributed under the permissive MIT License.
*/

#include "debug.h"

bool IsDebuggerAttached(void)
{
#ifdef __linux__
    ASSERT(0, "not implemented yet...")
    return false;
#elif _WIN32
    return IsDebuggerPresent();
#else
    return false;
#endif
}
