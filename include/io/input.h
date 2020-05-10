#pragma once

#include "def/defs.h"


#define PARAM_ARRIVAL_RATE      "arrivalrate"               // lambda
#define PARAM_DEPARTURE_RATE    "departurerate"             // mu
#define PARAM_LEAVING_RATE      "leavingrate"               // nu
#define PARAM_CHANNEL_NUM       "channelnum"                // n
#define PARAM_QUEUE_LEN         "queuelen"                  // m
#define PARAM_TIME_START        "timestart"
#define PARAM_TIME_END          "timeend"
#define PARAM_NUM_STEP          "numstep"


struct SmoInfo;

extern bool InputParseFile(const char* fname, struct SmoInfo* smo);
