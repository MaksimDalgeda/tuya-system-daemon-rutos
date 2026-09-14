#include <uci.h>

#include "ubus_internal.h"

Error_Code get_network_interfaces(network_info_t *network, size_t *network_count)
{
    struct uci_context *ctx;
    struct uci_package *pkg;
    struct uci_element *e;

    if (!network || !network_count)
        return ERROR;

    *network_count = 0;

    ctx = uci_alloc_context();
    if (!ctx)
        return ERROR;

    if (uci_load(ctx, "network", &pkg) != UCI_OK) {
        uci_free_context(ctx);
        return ERROR;
    }

    uci_foreach_element(&pkg->sections, e) {

        struct uci_section *s = uci_to_section(e);

        struct uci_option *proto;

        if (strcmp(s->type, "interface") != 0)
            continue;

        if (strcmp(s->e.name, "loopback") == 0)
            continue;
        
        proto = uci_lookup_option(ctx, s, "proto");

        if (proto && strcmp(proto->v.string, "dhcpv6") == 0)
            continue;

        strncpy(network[*network_count].name, s->e.name, sizeof(network[*network_count].name) - 1);

        network[*network_count].name[sizeof(network[*network_count].name) - 1] = '\0';

        (*network_count)++;
    }

    uci_unload(ctx, pkg);
    uci_free_context(ctx);

    return OK;
}