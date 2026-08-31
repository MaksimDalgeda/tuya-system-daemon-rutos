#include <stdio.h>
#include <syslog.h>
#include <unistd.h>

#include "tuya_agent_errors.h"
#include "tuyalink_core.h"
#include "tuya_cacert.h"
#include "system_info_service.h"

static tuya_mqtt_context_t client;
static bool connected = false;

void on_connected(tuya_mqtt_context_t *context, void *user_data)
{   
    (void)context;
    (void)user_data;
    
    connected = true;
    syslog(LOG_INFO, "Connected callback");
}

void on_disconnect(tuya_mqtt_context_t *context, void *user_data)
{
    (void)context;
    (void)user_data;

    connected = false;
    syslog(LOG_INFO, "Disconnected callback");
}

bool tuya_agent_is_connected(void)
{
    return connected;
}

void save_action_text(const char *text)
{
    FILE *fp = fopen("/tmp/tuya_action.log", "a");

    if (fp == NULL)
        return;

    fprintf(fp, "%s\n", text);

    syslog(LOG_INFO, "Action received: %s", text);

    fclose(fp);
}

static void on_messages(tuya_mqtt_context_t *context, void *user_data, const tuyalink_message_t *msg)
{
    (void)context;
    (void)user_data;

    if (msg == NULL)
        return;

    if (msg->type == THING_TYPE_ACTION_EXECUTE && msg->data_string != NULL){

        cJSON *root = cJSON_Parse(msg->data_string);
        if (root == NULL)
            return;

        cJSON *inputParams = cJSON_GetObjectItem(root, "inputParams");

        cJSON *text = cJSON_GetObjectItem(inputParams, "text");

        if (cJSON_IsString(text))
            save_action_text(text->valuestring);

        cJSON_Delete(root);
    }
}

Error tuya_agent_init(const char *deviceId,const char *deviceSecret)
{   
    int ret;

    ret = tuya_mqtt_init(&client,
        &(const tuya_mqtt_config_t)
        {
            .host = "m1.tuyacn.com",
            .port = 8883,

            .cacert = (const uint8_t *)tuya_cacert_pem,
            .cacert_len = sizeof(tuya_cacert_pem),

            .device_id = deviceId,
            .device_secret = deviceSecret,

            .keepalive = 60,
            .timeout_ms = 2000,

            .on_connected = on_connected,
            .on_disconnect = on_disconnect,
            .on_messages = on_messages,
        });

    if(ret != 0){
        syslog(LOG_WARNING, "tuya_mqtt_init failed: %d\n", ret);
        return ERROR_T;
    }

    syslog(LOG_INFO, "Tuya initialized\n");

    return OK_T;
}

Error tuya_agent_connect(void)
{
    int ret;

    ret = tuya_mqtt_connect(&client);

    if(ret != OK_T){
        syslog(LOG_WARNING, "tuya_mqtt_connect failed: %d\n", ret);
        return ERROR_T;
    }
    return OK_T;
}

void tuya_agent_loop(void)
{
    tuya_mqtt_loop(&client);
}

Error tuya_agent_send(const tuya_system_info_t *message)
{
    char payload[256];
    
    snprintf(payload,
         sizeof(payload),
         "{"
         "\"ram_free\":%.0f,"
         "\"ram_total\":%.0f,"
         "\"system_uptime\":%ld,"
         "\"cpu_usage\":%.1f,"
         "\"interface_name\":\"%s\","
         "\"ip_address\":\"%s\","
         "\"net_mask\":\"%s\","
         "\"transmitted_data_amount\":%.2f,"
         "\"received_data_amount\":%.2f"
         "}",
         message->free_ram_mb,
         message->total_ram_mb,
         message->uptime_s,
         message->cpu_usage_prcnt,
         message->network[0].name,
         message->network[0].ip,
         message->network[0].netmask,
         message->network[0].tx_mb,
         message->network[0].rx_mb);

    int ret = tuyalink_thing_property_report(&client, NULL, payload);

    //(LOG_INFO, "Property report sent: %s, id = %d", payload, ret); for logging send data

    return OK_T;
}