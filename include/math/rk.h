#pragma once

#include "def/defs.h"


typedef real(*rfunc_t)(const uint dim,
                       const uint func_idx,
                       const real arg,
                       const real y_vec[],
                       void* user_data);

struct RungeKuttaInfo
{
    real* MatA;             // compactified Ai,j = 0 when i <= j
    real* VecB;
    real* VecC;             // c[0] = 0!

    uint PrecOrder;
};

extern void RkInfoAlloc(const uint precision_order,
                        struct RungeKuttaInfo* rk);
extern void RkInfoFree(struct RungeKuttaInfo* rk);

extern real* RkGetA(const struct RungeKuttaInfo* rk,
                    const uint i, const uint j);
extern real* RkGetB(const struct RungeKuttaInfo* rk,
                    const uint i);
extern real* RkGetC(const struct RungeKuttaInfo* rk,
                    const uint i);

struct RungeKuttaContext
{
    real* K;
    real* YArg;
    real* YVecCopy;
};

extern void RkCtxInit(const struct RungeKuttaInfo* rk,
                      const uint dim,
                      struct RungeKuttaContext* rkctx);
extern void RkCtxFree(struct RungeKuttaContext* rkctx);

extern void RkMakeStep(const struct RungeKuttaInfo* rk,
                       const real dt,
                       const real arg,
                       const uint dim,
                       const rfunc_t rhs,
                       real y_vec[],
                       struct RungeKuttaContext* rkctx,
                       void* user_data);
