#pragma once

#include <stdbool.h>
#include <stddef.h>

#define SAFE_DEL(ptr) { free(ptr); (ptr) = NULL; }


typedef unsigned int uint;
typedef unsigned long ulong;
typedef double real;
