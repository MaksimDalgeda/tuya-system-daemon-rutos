#include <stdint.h>

#include "internal.h"
#include "ubus_internal.h"

Error_Code get_system_info(system_info_t *info){
    
    Error_Code err;

    err = get_cpu_usage(&info->cpu_usage_prcnt); 
    if(err > OK)
        return err;

    err = get_network_info(info->network, &info->network_count);//change to ubus
    if(err > OK)
        return err;

    err = ubus_get_system_info(info);
    if(err > OK)
        return err;

    return OK;
}

Error_Code initialize_ubus_connection(){

    Error_Code err = OK;

    err = initialize_ubus(); 
    if(err != OK)
        return err;

    err = ubus_get_object_ids();
     if(err != OK)
        return err;

    return OK;
}

Error_Code initialize_ubus_disconnect(){

    Error_Code err = OK;

    err = disconnect_ubus(); 

    return err;
}