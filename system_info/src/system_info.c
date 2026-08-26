#include <stdint.h>

#include "internal.h"

Error_Code get_system_info(system_info_t *info){
    
    Error_Code err;

    err = get_ram_info(&info->total_ram_bytes, &info->free_ram_bytes);
    if(err > 0) 
        return err;

    err = get_cpu_usage(&info->cpu_usage_prcnt);
    if(err > 0)
        return err;

    err = get_network_info(info->network, &info->network_count);
    if(err > 0)
        return err;

    err = get_uptime(&info->uptime_s);
     if(err > 0)
        return err;

    return err;
}