#include <stdio.h>
#include <syslog.h>

#include "tuya_agent_errors.h"
#include "system_info_service.h"
#include "system_info_convertor.h"
#include "signal_handler.h"

int main(int argc, char *argv[])
{   
    set_signal_action();

    Error err;
    system_info_t info;
    tuya_system_info_t message;

    //make daemon

    err = tuya_agent_init();
    if(err != OK_T)
        return err;

    err = tuya_agent_connect();
    if(err != OK_T)
        return err;

    while(!stop){
        
        tuya_agent_loop();
        err =  system_info_service(&info);
        if(err != OK_T)
            return err;
        err = convert_system_info(&info, &message);
        if(err != OK_T)
            return err;
        sleep(1);
    }
    return err;
}