#include "math/rk.h"
#include <stdlib.h>
#include <string.h>


void RkInfoAlloc(const uint precision_order,
                 struct RungeKuttaInfo* rk)
{
    const uint po = rk->PrecOrder = precision_order;

    rk->MatA = malloc((po*(po-1)/2)*sizeof(real));
    rk->VecB = malloc(po*sizeof(real));
    rk->VecC = malloc(po*sizeof(real));
    rk->VecC[0] = 0.0;
}

void RkInfoFree(struct RungeKuttaInfo* rk)
{
    rk->PrecOrder = 0;
    SAFE_DEL(rk->MatA);
    SAFE_DEL(rk->VecB);
    SAFE_DEL(rk->VecC);
}

real* RkGetA(const struct RungeKuttaInfo* rk,
             const uint i, const uint j)
{
    if(i <= j || rk->PrecOrder <= i)
        return NULL;

    return &rk->MatA[i*(i-1)/2 + j];
}

real* RkGetB(const struct RungeKuttaInfo* rk,
             const uint i)
{
    if(rk->PrecOrder <= i)
        return NULL;

    return &rk->VecB[i];
}

real* RkGetC(const struct RungeKuttaInfo* rk,
             const uint i)
{
    if(rk->PrecOrder <= i)
        return NULL;

    return &rk->VecC[i];
}

void RkCtxInit(const struct RungeKuttaInfo* rk,
               const uint dim,
               struct RungeKuttaContext* rkctx)
{
    rkctx->K        = malloc(rk->PrecOrder*dim*sizeof(real));
    rkctx->YArg     = malloc(dim*sizeof(real));
    rkctx->YVecCopy = malloc(dim*sizeof(real));
}

void RkCtxFree(struct RungeKuttaContext* rkctx)
{
    SAFE_DEL(rkctx->K);
    SAFE_DEL(rkctx->YArg);
    SAFE_DEL(rkctx->YVecCopy);
}

void RkMakeStep(const struct RungeKuttaInfo* rk,
                const real dt,
                const real arg,
                const uint dim,
                const rfunc_t rhs[],
                real y_vec[],
                struct RungeKuttaContext* rkctx)
{
    real* K          = rkctx->K;
    real* y_arg      = rkctx->YArg;
    real* y_vec_copy = rkctx->YVecCopy;
    memcpy(y_vec_copy, y_vec, dim*sizeof(real));

    // loop to eval K
    for(uint i = 0; i < rk->PrecOrder; ++i)
    {
        memcpy(y_arg, y_vec_copy, dim*sizeof(real));

        for(uint j = 0; j < i; ++j)
        {
            const uint K_bj = j*dim;                                            // K base index
            const real aij = *RkGetA(rk, i, j);
            for(uint r = 0; r < dim; ++r)
                y_arg[r] += dt*aij * K[K_bj + r];
        }

        const uint K_bi = i*dim;                                                // the same
        const real bi = *RkGetB(rk, i);
        const real ci = *RkGetC(rk, i);
        for(uint r = 0; r < dim; ++r)
        {
            K[K_bi + r] = (*rhs[r])(dim, arg + dt*ci, y_arg);
            y_vec[r] += dt*bi * K[K_bi + r];
        }
    }
}
