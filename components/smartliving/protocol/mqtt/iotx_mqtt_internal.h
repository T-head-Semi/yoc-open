 /*
 * Copyright (C) 2017-2024 Alibaba Group Holding Limited
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */



#ifndef __IOTX_MQTT_INTERNAL_H__
#define __IOTX_MQTT_INTERNAL_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "iot_import.h"
#include "exports/iot_export_mqtt.h"
#include "iotx_mqtt.h"

#define mqtt_emerg(...)             log_emerg("MQTT", __VA_ARGS__)
#define mqtt_crit(...)              log_crit("MQTT", __VA_ARGS__)
#define mqtt_err(...)               log_err("MQTT", __VA_ARGS__)
#define mqtt_warning(...)           log_warning("MQTT", __VA_ARGS__)
#define mqtt_info(...)              log_info("MQTT", __VA_ARGS__)
#define mqtt_debug(...)             log_debug("MQTT", __VA_ARGS__)


#define mqtt_malloc(size)            LITE_malloc(size, MEM_MAGIC, "mqtt")
#define mqtt_free                    LITE_free

#define MQTT_DYNBUF_SEND_MARGIN                      (64)

#define MQTT_DYNBUF_RECV_MARGIN                      (8)

/* Enlarge this buffer size due to add token params etc */
#define MQTT_CONNECT_REQUIRED_BUFLEN                 (384)

/* MQTT send publish packet */

#endif  /* __IOTX_MQTT_INTERNAL_H__ */
