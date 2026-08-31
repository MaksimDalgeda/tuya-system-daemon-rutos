#ifndef CLI_HANDLER_H
#define CLI_HANDLER_H

#include <stdbool.h>

#include "tuya_agent_errors.h"

typedef struct
{
    char *device_id;
    char *device_secret;
    char *product_id;
    bool daemon;

} Parameters;

static bool is_empty(const char *argumemt);
static error_t parse_opt(int key, char *arg, struct argp_state *state);
Error parse_args(int argc, char *argv[], Parameters * parameters);

#endif