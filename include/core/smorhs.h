#pragma once

#include "core/smoinfo.h"


// RHS for Kolmogorov ODE system
extern real SmoRhs(const uint dim, const uint func_idx,
                   const real arg, const real y_vec[],
                   void* user_data);
