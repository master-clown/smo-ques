#include "io/output.h"
#include <stdio.h>
#include "util/log.h"


bool OutputVecLst(const char* fn,
                  const char* title,
                  const real* vec_mat[],
                  const uint num_vec,
                  const uint dim)
{
    FILE* f;
    if(fopen_s(&f, fn, "w"))
    {
        LogPrintE("Cannot open file '%s' for vector output.", fn);
        return false;
    }

    fprintf(f, "%s\n\n\n%12s", title, "INDEX");
    for(uint i_v = 0; i_v < num_vec; ++i_v)
        fprintf(f, "%22s%02i", "VECTOR #", i_v);
    fprintf(f, "\n");

    for(uint r = 0; r < dim; ++r)
    {
        fprintf(f, "%12i", r+1);
        for(uint i_v = 0; i_v < num_vec; ++i_v)
            fprintf(f, "%24lf", vec_mat[i_v][r]);
        fprintf(f, "\n");
    }

    return true;
}
