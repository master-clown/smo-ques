#pragma once

#include "def/defs.h"


#define PARAM_ARRIVAL_RATE      "paramarrivalrate"              // lambda
#define PARAM_DEPARTURE_RATE    "paramdeparturerate"            // mu
#define PARAM_CHANNEL_NUM       "paramchannelnum"               // n
#define PARAM_QUEUE_LEN         "paramqueuelen"                 // m


struct SmoInfo;

extern bool InputParseFile(const char* fname, struct SmoInfo* smo);
