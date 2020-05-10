#include "util/thread.h"

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif


void ThreadSleep(const unsigned int msec)
{
#ifdef _WIN32
    Sleep(msec);
#else
    usleep(msec);
#endif
}
