#include "test/test.h"
#include "util/log.h"
#include "util/thread.h"


int TestLog(int argc, char* argv[])
{
    LogPrint("Hello, mister %s, age %i", "Jankowski", 25);
    LogPrintW("too much heat: x%i", 666);
    LogPrintE("Great '%s', jackass", "fmtdsk");
    LogPrintRaw("Nothing here\n");


    LogPrint("Testing carriage return...");
    LogSetAppendNewLineChar(false);

    ThreadSleep(2000);
    for(int i = 1; i <= 12; ++i)
    {
        LogMoveToLineBeg();
        LogPrint("Step count: %5i/%5i", i, 12);

        ThreadSleep(250);
    }

    LogPrintRaw("\n");
    LogSetAppendNewLineChar(true);

    LogPrint("Done");

    return 0;
}
