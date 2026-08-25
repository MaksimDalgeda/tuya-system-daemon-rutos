#ifndef SYSTEM_INFO_ERRORS_H
#define SYSTEM_INFO_ERRORS_H

typedef enum
{
    OK = 0,
    ERROR = 1,
    TUYA_CONNECT_ERROR =1,
    TUYA_AUTH_ERROR = 2,
    TUYA_TIME_OUT_ERROR =3,
    TUYA_SEND_ERROR = 4,
    CPU_ERROR = 5,
    RAM_ERROR = 6,
    NETWORK_ERROR = 7,
    UPTIME_ERROR = 8

} Error;

void print_error(Error error);

#endif