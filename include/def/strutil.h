#pragma once

#include <string.h>
#include "def/defs.h"


extern bool StrIsNullOrSpace(const char* str);
extern bool StrStartsWith(const char* str, const char* beg);

extern char* StrToLower(char* str);
