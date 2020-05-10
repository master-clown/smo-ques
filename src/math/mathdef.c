#include "math/mathdef.h"


int Clampi(const int val, const int min, const int max)
{
    return val < min ? min : (val > max ? max : val);
}

real Clampd(const real val, const real min, const real max)
{
    return val < min ? min : (val > max ? max : val);
}
