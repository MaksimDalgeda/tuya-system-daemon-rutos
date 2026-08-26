#include "tuya_agent_errors.h"

Error parser_error_code(Error_Code code)
{
    switch (code)
    {
        case OK:
            return OK_T;

        case CPU_READ_ERROR:
        case CPU_INVALID_ERROR:
            return ERROR_CPU_T;

        case RAM_ERROR:
            return ERROR_RAM_T;

        case NETWORK_ERROR:
            return ERROR_NETWORK_T;

        case UPTIME_ERROR:
            return ERROR_UPTIME_T;

        default:
            return ERROR_T;
    }
}