#include <string.h>
#include "system_info_convertor.h"



Error convert_system_info(system_info_t *info, tuya_system_info_t *message)
{    
    Error err = OK_T;

    message->total_ram_mb=convert_ram_to_mb(info->total_ram_bytes);
    message->free_ram_mb=convert_ram_to_mb(info->free_ram_bytes);
    message->cpu_usage_prcnt=info->cpu_usage_prcnt;
    message->uptime_s=info->uptime_s;
    message->network_count =(info->network_count > MAX_INTERFACES_TUYA)? MAX_INTERFACES_TUYA: info->network_count;

    for(size_t i = 0; i <message->network_count; i++){

        strncpy(message->network->name, info->network->name, sizeof(message->network->name) - 1);
        message->network->name[sizeof(message->network->name) - 1] = '\0';

        strncpy(message->network->ip, info->network->ip, sizeof(message->network->ip) - 1);
        message->network->ip[sizeof(message->network->ip) - 1] = '\0';

        strncpy(message->network->netmask, info->network->netmask, sizeof(message->network->netmask) - 1);
        message->network->netmask[sizeof(message->network->netmask) - 1] = '\0';


        message->network->rx_mb =convert_bytes_to_mb(info->network->rx_bytes);
        message->network->tx_mb = convert_bytes_to_mb(info->network->tx_bytes);

    }

    return OK_T;

}
double convert_ram_to_mb(long data)
{
    return (double)data / (1024.0 * 1024.0);
}
double convert_bytes_to_mb(uint64_t data)
{
    return (double)data / (1024.0 * 1024.0);
}