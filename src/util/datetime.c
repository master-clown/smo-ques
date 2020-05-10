#include "util/datetime.h"
#include <time.h>


void UtilGetCurrentTime(char buf[18])
{
    const time_t t = time(NULL);
    strftime(&buf[0], 18, "%d/%m/%y %H:%M:%S", localtime(&t));
}
