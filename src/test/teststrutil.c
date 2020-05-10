#include "test/test.h"

#include "def/strutil.h"
#include "util/log.h"


int TestStrUtil(int argc, char* argv[])
{
    // StrIsNullOrSpace()
//    LogPrint("%i", StrIsNullOrSpace(""));
//    LogPrint("%i", StrIsNullOrSpace("   "));
//    LogPrint("%i", StrIsNullOrSpace("   Hello"));
//    LogPrint("%i", StrIsNullOrSpace("   \t"));
//    LogPrint("%i", StrIsNullOrSpace("yes   "));
//    LogPrint("%i", StrIsNullOrSpace("   no "));

    // StrStartsWith()
//    LogPrint("%i", StrStartsWith("", "Some"));
//    LogPrint("%i", StrStartsWith("Some text", ""));
//    LogPrint("%i", StrStartsWith("Some text", "Some"));
//    LogPrint("%i", StrStartsWith("Some text", "some"));
//    LogPrint("%i", StrStartsWith("Some text", "Not some"));

    // StrToLower()
    LogPrint("%s", StrToLower(""));
    LogPrint("%s", StrToLower("    "));
    LogPrint("%s", StrToLower("nothing to change"));
    LogPrint("%s", StrToLower("Hello my Friend"));

    return 0;
}
