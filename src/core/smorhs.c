#include "core/smorhs.h"
#include "math/mathdef.h"


#pragma message("How to apply the normalizing equation? Sum{P_i(t)} = 1")

real SmoRhs(const uint dim, const uint func_idx,
            const real arg, const real y_vec[],
            void* user_data)
{
    struct SmoInfo* si = user_data;

    if(1 <= func_idx && func_idx < dim-1)
    {
        //const real f1 = si->ArrivalRate;
        const real f2 = si->ArrivalRate
                      + Clampi(func_idx, 1, si->ChannelNum)*si->DepartureRate
                      + (func_idx > si->ChannelNum ? (func_idx - si->ChannelNum) : 0.0)
                        *si->LeavingRate;
        const real f3 = (Clampi(func_idx, 1, si->ChannelNum-1) + 1)*si->DepartureRate
                        + (func_idx >= si->ChannelNum ? (func_idx - si->ChannelNum + 1) : 0.0)
                          *si->LeavingRate;

        return si->ArrivalRate * y_vec[func_idx-1] - f2 * y_vec[func_idx] + f3 * y_vec[func_idx+1];
    }
    else
    if(func_idx <= 1)
    {
        return -si->ArrivalRate*y_vec[0] + si->DepartureRate*y_vec[1];
    }
    else
    {
        return si->ArrivalRate*y_vec[dim-2] - (si->ChannelNum*si->DepartureRate
                                             + si->QueueLen*si->LeavingRate)*y_vec[dim-1];
    }
}
