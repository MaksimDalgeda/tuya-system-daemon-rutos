#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <ifaddrs.h>
#include <netinet/in.h>//sockaddr_in in_addr
#include <arpa/inet.h>//inet_ntop

#include "internal.h"

void get_interface_stats(char *name, uint64_t *rx_bytes,uint64_t *tx_bytes)
{
    char path[256];
    FILE *fp;

    *rx_bytes = 0;
    *tx_bytes = 0;

    snprintf(path, sizeof(path), "/sys/class/net/%s/statistics/rx_bytes",name);

    fp = fopen(path, "r");
    if (fp != NULL) {
        fscanf(fp, "%lu", rx_bytes);
        fclose(fp);
    }

    snprintf(path, sizeof(path), "/sys/class/net/%s/statistics/tx_bytes", name);

    fp = fopen(path, "r");
    if (fp != NULL) {
        fscanf(fp, "%lu", tx_bytes);
        fclose(fp);
    }
}

Error_Code get_network_info(network_info_t *network, size_t *network_count)
{   
    if (network == NULL || network_count == NULL)
        return ERROR;
    
    struct ifaddrs *ifaddr;

    if (getifaddrs(&ifaddr) == -1)
        return NETWORK_ERROR;

    *network_count = 0;

    for (struct ifaddrs *ifa = ifaddr;ifa != NULL; ifa = ifa->ifa_next)
    {
        if (*network_count >= MAX_INTERFACES)
            break;

        if (ifa->ifa_addr == NULL)
            continue;
        if (strcmp(ifa->ifa_name, "lo") == 0)
        continue;
        
        if (ifa->ifa_addr->sa_family != AF_INET) //AF_INET ipv4  AF_INET6 ipv6
            continue;

            
        network_info_t *iface = &network[*network_count];

        memset(iface, 0, sizeof(*iface));

        strncpy( iface->name, ifa->ifa_name, sizeof(iface->name) - 1);

        if(inet_ntop(AF_INET, &((struct sockaddr_in *)ifa->ifa_addr)->sin_addr, iface->ip, sizeof(iface->ip)) == NULL)
            return NETWORK_ERROR;

        if (ifa->ifa_netmask != NULL)
            inet_ntop(AF_INET, &((struct sockaddr_in *)ifa->ifa_netmask)->sin_addr, iface->netmask, sizeof(iface->netmask));

        get_interface_stats(iface->name, &iface->rx_bytes, &iface->tx_bytes);

        (*network_count)++;
    }

    freeifaddrs(ifaddr);

    return OK;
}