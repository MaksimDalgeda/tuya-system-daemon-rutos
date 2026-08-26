#ifndef SYSTEM_INFO_INTERNAL_H
#define SYSTEM_INFO_INTERNAL_H

#include "system_info.h"

Error_Code get_cpu_usage(double *usage);
Error_Code read_cpu_times(unsigned long long *idle, unsigned long long *total);

Error_Code get_ram_info(long *total_ram,long *free_ram);

Error_Code get_uptime(long *uptime);

Error_Code get_network_info(network_info_t *network, size_t *network_count);
void get_interface_stats(char *name, uint64_t *rx_bytes,uint64_t *tx_bytes);

#endif