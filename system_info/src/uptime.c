#include <sys/sysinfo.h>

#include "internal.h"

Error_Code get_uptime(long *uptime){

    struct sysinfo info;
    if(sysinfo(&info) != 0)
        return UPTIME_ERROR;
    
    *uptime = info.uptime;
    return OK;
}