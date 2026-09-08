#ifndef UBUS_INTERNAL_H
#define UBUS_INTERNAL_H

#include "ubus.h"

Error_Code ubus_get_system_info(system_info_t *info); //uptime, memory 
Error_Code ubus_get_system_network(); //name, ip , netmask
Error_Code ubus_get_traffic(); //trafic data

#endif