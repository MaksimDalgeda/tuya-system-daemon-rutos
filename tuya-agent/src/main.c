#include <stdio.h>
#include <syslog.h>

#include "system_info.h"

int main(int argc, char *argv[])
{
    system_info_t info;
    Error_Code ret;

    ret = get_system_info(&info);

    printf("\nRam total - %ld\nRam free - %ld\n", info.total_ram_bytes, info.free_ram_bytes);
    printf("\nCPU usage - %.2f\n", info.cpu_usage_prcnt);
    
    return ret;
}
