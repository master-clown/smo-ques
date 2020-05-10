#pragma once

#include "def/defs.h"


struct SmoInfo
{
    real SimTimeBeg;
    real SimTimeEnd;
    uint SimNumStep;

    real ArrivalRate;
    real DepartureRate;
    real LeavingRate;

    ulong ChannelNum;
    ulong QueueLen;
};
