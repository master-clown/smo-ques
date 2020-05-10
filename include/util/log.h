#pragma once

//#include "def/string.hpp"
#include "def/defs.h"


extern void LogPrint(const char* msg, ...);                        // Message
extern void LogPrintW(const char* msg, ...);                       // Warning
extern void LogPrintE(const char* msg, ...);                       // Error
extern void LogPrintRaw(const char* msg, ...);                     // Print exactly "msg" without additions.

extern void LogMoveToLineBeg();
extern void LogSetAppendNewLineChar(const bool add_new_line);      // for next "Print*()" call set new line char append
extern void LogFlushBuffer();
