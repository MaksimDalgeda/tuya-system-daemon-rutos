#include "system_info_service.h" 
#include "system_info.h"
#include "system_info_convertor.h"

Error system_info_service_start(void){

    system_info_t info;
    tuya_system_info_t message;
    Error_Code ret;
    Error err;

    while(1){
        ret = get_system_info(&info);
        err = parser_error_code(ret);

        if(err != OK)
            return err;//err validation

        err = convert_system_info(&info, &message);
        
        printf("\nSystem Uptime - %ld\n", info.uptime_s);
        printf("Ram total - %ld\nRam free - %ld\n", info.total_ram_bytes, info.free_ram_bytes);
        printf("CPU usage - %.2f\n", info.cpu_usage_prcnt);

        for(size_t i = 0; i < info.network_count; i++){
            printf("\nNetwork %ld\n", i + 1);
            printf("Network name - %s\n", info.network[i].name);
            printf("Network ip- %s\n", info.network[i].ip);
            printf("Network mask - %s\n", info.network[i].netmask);
            printf("Received data amount  - %ld\n", info.network->rx_bytes);
            printf("Transmitted data amount - %ld\n", info.network->tx_bytes);
        }
        sleep(2);

    }
}