#pragma once

#include "def/defs.h"


extern bool OutputVecLst(const char* fn,
                         const char* title,
                         const char* gr_title_lst[],
                         const real* vec_mat[],
                         const uint num_vec,
                         const uint dim);
