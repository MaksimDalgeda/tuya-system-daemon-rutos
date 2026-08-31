#ifndef SYSTEM_INFO_CONVERTOR_H
#define SYSTEM_INFO_CONVERTOR_H

#include "system_info.h"
#include "system_info_service.h"

Error convert_system_info(system_info_t *info, tuya_system_info_t *message);

#endif

