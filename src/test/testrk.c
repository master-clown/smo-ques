#include "test/test.h"
#include <math.h>
#include <stdlib.h>
#include "io/output.h"
#include "math/rk.h"
#include "util/log.h"


static void InitRkThreeEighth(struct RungeKuttaInfo* rk);
static real TestRhs1(const uint dim, const real arg, const real y_vec[]);
static real TestRhs2(const uint dim, const real arg, const real y_vec[]);
static real TestRef1(const uint dim, const real arg, const real y_vec[]);           // reference solution
static real TestRef2(const uint dim, const real arg, const real y_vec[]);

int TestRungeKutta(int argc, char* argv[])
{
#define DIM 2

    struct RungeKuttaInfo rk;
    struct RungeKuttaContext rkctx;
    InitRkThreeEighth(&rk);
    RkCtxInit(&rk, DIM, &rkctx);

    const rfunc_t rhs[] = { &TestRhs1, &TestRhs2 };
    const real a = 0.0;
    const real b = 2.0;
    const uint ndiv = 100;
    const real dt = (b - a) / ndiv;

    real* solx = malloc((ndiv+1)*sizeof(real));
    real* soly = malloc((ndiv+1)*sizeof(real));
    real* refx = malloc((ndiv+1)*sizeof(real));
    real* refy = malloc((ndiv+1)*sizeof(real));

    // initial conditions
    solx[0] = refx[0] = soly[0] = refy[0] = 0.0;

    real time = 0.0;
    real cv[DIM]  = { solx[0], soly[0] };                                                // current value (at current step)
    real rcv[DIM] = { refx[0], refy[0] };                                                // reference cv
    for(uint s = 0; s < ndiv; ++s)
    {
        time += dt;

        RkMakeStep(&rk, dt, time, DIM, rhs, cv, &rkctx);
        solx[s+1] = cv[0]; soly[s+1] = cv[1];

        refx[s+1] = TestRef1(DIM, time, rcv);
        refy[s+1] = TestRef2(DIM, time, rcv);
    }

    const real* vec_lst[] = { solx, refx, soly, refy };
    OutputVecLst("test/TestRungeKutta/sol.txt",
                 "SOLUTION COMPARISON",
                 vec_lst, 2*DIM, ndiv+1);

    free(refy);
    free(refx);
    free(soly);
    free(solx);
    RkCtxFree(&rkctx);
    RkInfoFree(&rk);

    return 0;
}


static void InitRkThreeEighth(struct RungeKuttaInfo* rk)
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

static real TestRhs1(const uint dim, const real arg, const real y_vec[])
{
    return y_vec[0] - 1;
}

static real TestRhs2(const uint dim, const real arg, const real y_vec[])
{
    return y_vec[0] + 2*y_vec[1] - 3;
}

static real TestRef1(const uint dim, const real arg, const real y_vec[])
{
    return 1 - exp(arg);
}

static real TestRef2(const uint dim, const real arg, const real y_vec[])
{
    return exp(arg) - 2*exp(2*arg) + 1;
}
