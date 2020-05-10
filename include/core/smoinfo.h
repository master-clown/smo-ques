#pragma once

#include "def/defs.h"


struct SmoInfo
{
    real ArrivalRate;
    real DepartureRate;

    ulong ChannelNum;
    ulong QueueLen;
};
