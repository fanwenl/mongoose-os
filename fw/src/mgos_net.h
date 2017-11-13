/*
 * Copyright (c) 2014-2017 Cesanta Software Limited
 * All rights reserved
 */

/*
 * Low-level network configuration API.
 *
 * Contains definitions of the configuration state. Allows to set up an
 * event handler that tracks state changes: when the network connectivity
 * is lost, established, etc.
 */

#ifndef CS_FW_SRC_MGOS_NET_H_
#define CS_FW_SRC_MGOS_NET_H_

#include <stdbool.h>

#include "mongoose/mongoose.h"

#include "mgos_config.h"
#include "mgos_init.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

enum mgos_net_event {
  MGOS_NET_EV_DISCONNECTED = 0,
  MGOS_NET_EV_CONNECTING = 1,
  MGOS_NET_EV_CONNECTED = 2,
  MGOS_NET_EV_IP_ACQUIRED = 3,
};

enum mgos_net_if_type {
  MGOS_NET_IF_TYPE_WIFI,
  MGOS_NET_IF_TYPE_ETHERNET,
  MGOS_NET_IF_TYPE_PPP,
  /* This is a sentinel in case all networking interface types are disabled. */
  MGOS_NET_IF_MAX,
};

struct mgos_net_ip_info {
  struct sockaddr_in ip;
  struct sockaddr_in netmask;
  struct sockaddr_in gw;
};

struct mgos_net_event_data {
  enum mgos_net_if_type if_type;
  int if_instance;
  struct mgos_net_ip_info ip_info;
};

/* Event handler signature. */
typedef void (*mgos_net_event_handler_t)(
    enum mgos_net_event ev, const struct mgos_net_event_data *ev_data,
    void *arg);

/* Register network configuration event handler. */
void mgos_net_add_event_handler(mgos_net_event_handler_t eh, void *arg);

/* Unregister network configuration event handler. */
void mgos_net_remove_event_handler(mgos_net_event_handler_t eh, void *arg);

/* Retrieve IP configuration. */
bool mgos_net_get_ip_info(enum mgos_net_if_type if_type, int if_instance,
                          struct mgos_net_ip_info *ip_info);

/*
 * Converts address to dotted-quad NUL-terminated string.
 * out must be at least 16 bytes long.
 */
void mgos_net_ip_to_str(const struct sockaddr_in *sin, char *out);

enum mgos_init_result mgos_net_init(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* CS_FW_SRC_MGOS_NET_H_ */
