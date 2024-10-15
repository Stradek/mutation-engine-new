#include "debug.h"

bool is_debugger_attached(void)
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
