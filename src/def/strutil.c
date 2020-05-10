#include "def/strutil.h"
#include <ctype.h>


bool StrIsNullOrSpace(const char* str)
{
    if(!str)
        return true;

    while(*str && isspace(*str))
        ++str;

    return !(*str);
}

bool StrStartsWith(const char* str, const char* beg)
{
    return strncmp(str, beg, strlen(beg)) == 0;
}


char* StrToLower(char* str)
{
    if(!str)
        return str;

    for(char* it = str; *it; ++it)
        *it = tolower(*it);

    return str;
}
