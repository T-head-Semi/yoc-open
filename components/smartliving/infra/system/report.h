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



#ifndef __IOTX_REPORT_H__
#define __IOTX_REPORT_H__

typedef int (*info_report_func_pt)(void *handle, const char *topic_name,int req_ack,void *data, int len); 

#define MIDREPORT_PAYLOAD_LEN             (62 + PID_STRLEN_MAX + MID_STRLEN_MAX + 32 +1)
#define MIDREPORT_REQID_LEN               (PRODUCT_KEY_LEN + DEVICE_NAME_LEN + 6)
#define AOS_VERSON_MSG_LEN                (256)
#define LINKKIT_VERSION_MSG_LEN           (192)
#define FIRMWARE_VERSION_MSG_LEN          (128)
#define DEBUG_REPORT_MID_DEVINFO_FIRMWARE (1)

int     iotx_report_id(void);
int     iotx_midreport_reqid(char *requestId, char *product_key, char *device_name);
int     iotx_midreport_payload(char *msg, char *requestId, char *mid, char *pid);
int     iotx_midreport_topic(char *topic_name, char *topic_head, char *product_key, char *device_name);

/* AOS version report API */
int     iotx_gen_aos_report_topic(char *topic_name, char *product_key, char *device_name);
int     iotx_gen_aos_report_payload(char *msg, int requestId, char *versionData);

#ifndef BUILD_AOS
unsigned int aos_get_version_info(unsigned char version_num[VERSION_NUM_SIZE],
                                  unsigned char random_num[RANDOM_NUM_SIZE], unsigned char mac_address[MAC_ADDRESS_SIZE],
                                  unsigned char chip_code[CHIP_CODE_SIZE], unsigned char *output_buffer, unsigned int output_buffer_size);
#endif

void iotx_set_report_func(info_report_func_pt func);
int iotx_report_devinfo(void *pclient);
int iotx_report_mid(void *pclient);
int iotx_report_firmware_version(void *pclient);
void iotx_report_connect_status (void *pclient, uint32_t conn_cost);

#endif