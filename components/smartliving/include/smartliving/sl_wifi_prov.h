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

#ifndef __SL_WIFI_PROV_H__
#define __SL_WIFI_PROV_H__
#if defined(__cplusplus)
extern "C" {
#endif

/** register smartliving wifi provisioning method, include both smartconfig and device ap
  * @return 0 success, else failed
 */
int wifi_prov_sl_register();

/** report provisioning success result to cloud, do device biding with cellphone
 */
void wifi_prov_sl_start_report();

/** stop reporting to cloud, reporting thread would stop asyncrously
 */
void wifi_prov_sl_stop_report();

/** set wifi connect state after provisioning
 * @param connected 1：连接成功；0：连接失败
 */
void wifi_prov_sl_set_connected(int connected);

#if defined(__cplusplus)
}
#endif
#endif  /* __SL_WIFI_PROV_H__ */

