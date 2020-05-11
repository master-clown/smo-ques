#include "core/solve.h"
#include <stdlib.h>
#include "core/smoinfo.h"
#include "core/smorhs.h"
#include "io/output.h"
#include "math/rk.h"
#include "math/rk_three_eighth.h"
#include "util/log.h"


void SmoSolve(struct SmoInfo* si)
{
    const uint dim = si->ChannelNum + si->QueueLen + 1;
    struct RungeKuttaInfo rk;
    struct RungeKuttaContext rkctx;
    RkThreeEighthInit(&rk);
    RkCtxInit(&rk, dim, &rkctx);

    const uint ndiv = si->SimNumStep;
    const real dt = (si->SimTimeEnd - si->SimTimeBeg) / ndiv;
    const uint tm = ndiv + 1;                                                           // number of time moments kept in memory

    real* sol = malloc(dim*tm*sizeof(real));
    real* cv  = malloc(dim*sizeof(real));                                               // current values (at current step)

    // initial conditions
    for(uint i = 1; i < dim; ++i) sol[i*tm] = 0.0;
    sol[0] = 1.0;

    real time = si->SimTimeBeg;
    for(uint s = 0; s < ndiv; ++s)
    {
        time += dt;

        for(uint i = 0; i < dim; ++i) cv[i] = sol[s + i*tm];

        RkMakeStep(&rk, dt, time, dim, &SmoRhs, cv, &rkctx, si);

        for(uint i = 0; i < dim; ++i) sol[s+1 + i*tm] = cv[i];
    }

    const real* vec_lst[10] = { &sol[0*tm], &sol[1*tm],
                                &sol[2*tm],

                                            &sol[3*tm],
                                &sol[4*tm], &sol[5*tm],
                                &sol[6*tm], &sol[7*tm],
                                &sol[6*tm], &sol[7*tm] } ;

    const char* gr_title_lst[] =
    {
        "P[0](t)", "P[1](t)", "P[2](t)", "P[2+1](t)", "P[2+2](t)", "P[2+3](t)",
        "P[2+4](t)", "P[2+5](t)", "P[2+6](t)", "P[2+7](t)", "P[2+8](t)"
    };

    OutputVecLst("test/solve/sol.txt",
                 "", gr_title_lst,
                 vec_lst, 10, ndiv+1);

    real sum = 0.0, sum_plot = 0.0;
    for(uint i = 0; i < dim; ++i) sum += cv[i];
    for(uint i = 0; i < 10; ++i) sum_plot += cv[i];

    LogPrint("The sum of solution at the last time moment         = %.15lf", sum);
    LogPrint("The sum of plotted solution at the last time moment = %.15lf", sum_plot);

    free(cv);
    free(sol);
    RkCtxFree(&rkctx);
    RkInfoFree(&rk);
}
