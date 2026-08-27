#include <stdio.h>

#include "tuyalink_core.h"

#include "tuya_agent.h"
#include "tuya_agent_errors.h"
#include "tuya_cacert.h"

static tuya_mqtt_context_t client;

static const char deviceId[] = "269be577b3e64f5dbd95js";

static const char deviceSecret[] = "VBv8CcB8EdgffeLp";

static void on_connected(tuya_mqtt_context_t *context, void *user_data)
{
    (void)context;
    (void)user_data;

    printf("Connected to Tuya Cloud\n");
}

static void on_disconnect(tuya_mqtt_context_t *context, void *user_data)
{
    (void)context;
    (void)user_data;

    printf("Disconnected from Tuya Cloud\n");
}

static void on_messages(tuya_mqtt_context_t *context, void *user_data, const tuyalink_message_t *msg)
{
    (void)context;
    (void)user_data;

    printf("Message received\n");

    if(msg == NULL){
        return;
    }

    printf("msg id : %s\n", msg->msgid);
    printf("type   : %d\n", msg->type);
    printf("code   : %d\n", msg->code);

    printf("payload: %s\n", msg->data_string);
    
    if(msg->data_string != NULL){
        printf("payload: %s\n", msg->data_string);
    }
}

Error tuya_agent_init(void)
{
    int ret;

    ret = tuya_mqtt_init(&client,
        &(const tuya_mqtt_config_t)
        {
            .host = "m1.tuyacn.com",
            .port = 8883,

            .cacert = tuya_cacert_pem,
            .cacert_len = sizeof(tuya_cacert_pem),

            .device_id = deviceId,
            .device_secret = deviceSecret,

            .keepalive = 60,
            .timeout_ms = 2000,

            .on_connected = on_connected,
            .on_disconnect = on_disconnect,
            .on_messages = on_messages,
        });

    if(ret != OK_T){
        printf("tuya_mqtt_init failed: %d\n", ret);
        return ERROR_T;
    }

    printf("Tuya initialized\n");

    return OK_T;
}

Error tuya_agent_connect(void)
{
    int ret;

    ret = tuya_mqtt_connect(&client);

    if(ret != OK_T){
        printf("tuya_mqtt_connect failed: %d\n", ret);
        return ERROR_T;
    }

    printf("Connecting to cloud...\n");

    return OK_T;
}

void tuya_agent_loop(void)
{
    tuya_mqtt_loop(&client);
}