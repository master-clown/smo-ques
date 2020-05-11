#include "test/test.h"
#include "io/output.h"
#include "util/log.h"


int TestIo(int argc, char* argv[])
{
    const real lst1[7] = { 0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0 };
    const real lst2[7] = { 0.5, 1.5, 2.5, 3.5, 4.5, 5.5, 6.5 };
    const real* lst[] = { lst1, lst2 };

    // add graphs' titles
//    OutputVecLst("test/OutputVecLst()/output.txt",
//                 "TWO REAL VECTORS",
//                 lst, 2, 7);

    return 0;
}
