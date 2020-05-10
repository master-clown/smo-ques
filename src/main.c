#include "core/smoinfo.h"
#include "io/input.h"
#include "test/test.h"
#include "util/log.h"


int main(int argc, char* argv[])
{
    main_test(argc, argv);
    return 0;

    if(argc < 2)
    {
        LogPrintE("Pass input file as the second cmd-line argument");
        return 1;
    }

    struct SmoInfo smo;
    if(!InputParseFile(argv[1], &smo))
        return 2;

    for(int i = 1; i < 10; ++i)
        for(int j = 0; j < i; ++j)
            LogPrintRaw("%i, ", i*(i-1)/2 + j);

    LogPrintRaw("\n");

    return 0;
}
