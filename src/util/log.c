#include "util/log.h"
#include <stdarg.h>
#include <stdio.h>
#include "util/datetime.h"


#define PASS_VARARG(msg, msg_type)          \
    va_list argptr;                         \
    va_start(argptr, msg);                  \
    PrintLog(msg_type, msg, argptr);        \
    va_end(argptr);                         \


static bool gAppendNewLineChar = true;

static void PrintLog(const int type, const char* msg, va_list arglst);          // 0 - msg, 1 - warn, 2 - error


void LogPrint(const char* msg, ...)                        // Message
{
    PASS_VARARG(msg, 0)
}

void LogPrintW(const char* msg, ...)                       // Warning
{
    PASS_VARARG(msg, 1)
}

void LogPrintE(const char* msg, ...)                       // Error
{
    PASS_VARARG(msg, 2)
}

void LogPrintRaw(const char* msg, ...)                     // Print exactly "msg" without additions.
{
    va_list argptr;
    va_start(argptr, msg);
    vprintf(msg, argptr);
    va_end(argptr);
}

void LogMoveToLineBeg()
{
    putchar('\r');
}

void LogSetAppendNewLineChar(const bool add_new_line)
{
    gAppendNewLineChar = add_new_line;
}

void LogFlushBuffer()
{
    fflush(stdout);
}


void PrintLog(const int type, const char* msg, va_list arglst)
{
    char timebuf[18];
    UtilGetCurrentTime(timebuf);

    printf("%s> ", timebuf);

    if(type == 1) printf("[WARN] ");
    else
    if(type == 2) printf("[ERROR] ");

    vprintf(msg, arglst);

    if(gAppendNewLineChar)
        putchar('\n');
}
