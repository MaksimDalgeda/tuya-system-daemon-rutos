#ifndef TUYA_AGENT_H
#define TUYA_AGENT_H

#include "tuya_agent_errors.h"
#include "tuya_agent.h"
#include "system_info_service.h"


Error tuya_agent_init(const char *deviceId,const char *deviceSecret,const char *productId);
Error tuya_agent_connect(void);
void tuya_agent_loop(void);

Error tuya_agent_send(const tuya_system_info_t *message);
void save_action_text(const char *text);

#endif