#include <argp.h>
#include <string.h>

#include "cli_handler.h"

const char *argp_program_version = "tuya-monitor-daemon 1.0";
const char *argp_program_bug_address = "";

static struct argp_option options[] = {
    {"device-id",     'd', "ID",      0, "Device ID"},
    {"device-secret", 's', "SECRET",  0, "Device Secret"},
    {"product-id",    'p', "PID",     0, "Product ID"},
    {"daemon",        'D', 0,         0, "Run as daemon"},
    {0}
};

static error_t parse_opt(int key, char *arg, struct argp_state *state)
{
    Parameters *params = state->input;

    switch (key) {

    case 'd':
        params->device_id = arg;
        break;

    case 's':
        params->device_secret = arg;
        break;

    case 'p':
        params->product_id = arg;
        break;

    case 'D':
        params->daemon = true;
        break;

    case ARGP_KEY_END:

        if (!params->device_id)
            argp_error(state, "--device-id is required");

        if (!params->device_secret)
            argp_error(state, "--device-secret is required");

        if (!params->product_id)
            argp_error(state, "--product-id is required");

        break;

    default:
        return ARGP_ERR_UNKNOWN;
    }

    return 0;
}

static struct argp argp = { options,parse_opt };

Error parse_args(int argc, char *argv[], Parameters *parameters)
{
    memset(parameters, 0, sizeof(*parameters));

    argp_parse(&argp,argc,argv,0,0,parameters);

    if(!parameters->device_id || !parameters->device_secret || !parameters->product_id)
        return ERROR_PARSE_T;

    return OK_T;
}