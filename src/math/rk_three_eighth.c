#include "math/rk_three_eighth.h"
#include "math/rk.h"


void RkThreeEighthInit(struct RungeKuttaInfo* rk)
{
    RkInfoAlloc(4, rk);

    *RkGetA(rk, 1, 0) = 1/3.0;
    *RkGetA(rk, 2, 0) =-1/3.0;
    *RkGetA(rk, 2, 1) = *RkGetA(rk, 3, 0) = *RkGetA(rk, 3, 2) = 1.0;
    *RkGetA(rk, 3, 1) =-1.0;

    *RkGetB(rk, 0) = *RkGetB(rk, 3) = 1/8.0;
    *RkGetB(rk, 1) = *RkGetB(rk, 2) = 3/8.0;

    *RkGetC(rk, 1) = 1/3.0;
    *RkGetC(rk, 2) = 2/3.0;
    *RkGetC(rk, 3) = 1.0;
}
