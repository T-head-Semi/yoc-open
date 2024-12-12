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


#include <devices/netdrv.h>

int ping(int type, char *remote_ip)
{
    rvm_dev_t *wifi_dev = rvm_hal_device_find("wifi", 0);
    if (wifi_dev != NULL) {
        rvm_hal_net_ping(wifi_dev, type, remote_ip);
    }

	rvm_dev_t *gprs_dev = rvm_hal_device_find("gprs", 0);
    if (gprs_dev != NULL) {
        rvm_hal_net_ping(gprs_dev, type, remote_ip);
    }

    return 0;
}

