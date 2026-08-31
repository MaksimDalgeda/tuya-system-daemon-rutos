#include "system_info_service.h" 
#include "system_info_convertor.h"

Error system_info_service(system_info_t * info)
{
    Error_Code ret;
    Error err;

        ret = get_system_info(info);
        err = parser_error_code(ret);

    return err;
}