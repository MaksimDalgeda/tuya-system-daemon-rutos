#ifndef TUYA_AGENT_ERRORS_H
#define TUYA_AGENT_ERRORS_H

#include "system_info_errors.h"

typedef enum
{
    OK_T = 0,
    ERROR_T = 1,
    ERROR_CONNECT_T =1,
    ERROR_TUYA_AUTH_T = 2,
    ERROR_TUYA_TIME_OUT_T =3,
    ERROR_TUYA_SEND_T = 4,
    ERROR_CPU_T = 5,
    ERROR_RAM_T = 6,
    ERROR_NETWORK_T = 7,
    ERROR_UPTIME_T = 8,
    ERROR_PARSE_T = 9,

} Error;

Error parser_error_code(Error_Code error);
#endif