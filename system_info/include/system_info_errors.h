#ifndef SYSTEM_INFO_ERRORS_H
#define SYSTEM_INFO_ERRORS_H

typedef enum
{
    OK = 0,
    ERROR = 1,
    CPU_READ_ERROR = 2,
    CPU_INVALID_ERROR = 3,
    RAM_ERROR = 4,
    NETWORK_ERROR = 5,
    UPTIME_ERROR = 6

} Error_Code;

#endif
