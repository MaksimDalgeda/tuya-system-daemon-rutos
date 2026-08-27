#ifndef TUYA_AGENT_H
#define TUYA_AGENT_H

#include "tuya_agent_errors.h"

Error tuya_agent_init(void);
Error tuya_agent_connect(void);
void tuya_agent_loop(void);


#endif