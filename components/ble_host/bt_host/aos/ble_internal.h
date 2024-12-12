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

#ifndef __BLE_BLE_INTERNALH__
#define __BLE_BLE_INTERNALH__

#ifdef __cplusplus
extern "C"
{
#endif

    void le_auth_passkey_display(struct bt_conn *conn, unsigned int passkey);

    void le_auth_passkey_confirm(struct bt_conn *conn, unsigned int passkey);

    void le_auth_passkey_entry(struct bt_conn *conn);

    void le_auth_cancel(struct bt_conn *conn);

    void le_auth_pairing_confirm(struct bt_conn *conn);

    void le_auth_pairing_complete(struct bt_conn *conn, bool bonded);

    void le_auth_pairing_failed(struct bt_conn *conn, enum bt_security_err reason);

#ifdef __cplusplus
}
#endif

#endif /* __BLE_BLE_INTERNALH__ */
