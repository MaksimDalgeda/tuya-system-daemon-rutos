#include <sys/sysinfo.h>
#include <stddef.h>

#include "system_info.h"


Error_Code get_ram_info(long *total_ram,long *free_ram)
{
    struct sysinfo info;

    if (free_ram == NULL || total_ram == NULL)
        return RAM_ERROR;
        
    if (sysinfo(&info) == -1)
        return RAM_ERROR;//maybe create sys_info_error

    *total_ram = info.totalram;
    *free_ram = info.freeram;

    return 0;
}