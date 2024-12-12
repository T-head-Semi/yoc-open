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

#if defined(CONFIG_BOARD_BT) && CONFIG_BOARD_BT

#include <aos/aos.h>
#include <aos/bt.h>
#include <aos/cli.h>

#define CLI_BT_PRINTF(mod, fmt, ...) printf("[bt %s]" fmt, (mod), ##__VA_ARGS__)
#define CLI_BT_PRINTF_D(fmt, ...)    CLI_BT_PRINTF(argv[0], "[DBG]" fmt, ##__VA_ARGS__)
#define CLI_BT_PRINTF_I(fmt, ...)    CLI_BT_PRINTF(argv[0], " " fmt, ##__VA_ARGS__)
#define CLI_BT_PRINTF_E(fmt, ...)    CLI_BT_PRINTF(argv[0], "[ERR]" fmt, ##__VA_ARGS__)

#define CMD_SET_IO_HELP_INFO "bt set_io <io_cap: (DisplayOnly, DisplayYesNo, KeyboardOnly, None, KeyboardDisplay)>"
#define CMD_UNPAIR_HELP_INFO "bt unpair_dev <device address: (All, XX:XX:XX:XX:XX:XX)> [type: (public, random)]"
#define CMD_SET_EIR_HELP_INFO                                                                                          \
    "bt set_eir <fec_required> <eir_data(len(1byte)|type(1byte)|data(len -1 bytes)...), eg. bt set_eir "               \
    "020106050954455354>"
#define CMD_UPDATE_EIR_HELP_INFO                                                                                       \
    "bt update_eir <eir_data(len(1byte)|type(1byte)|data(len -1 bytes)...), eg. bt update_eir "                        \
    "020106050954455354>"

#define CMD_AVRCP_HELP_INFO                                                                                            \
    "\n\tbt avrcp ct_init\n"                                                                                           \
    "\tbt avrcp tg_init\n"                                                                                             \
    "\tbt avrcp register [1 ~ 13]\n"                                                                                   \
    "\tbt avrcp pt [operation_id] [operation_state]\n"                                                                 \
    "\tbt avrcp get_ps\n"                                                                                              \
    "\tbt avrcp set_abs_vol [0 ~ 127]\n"                                                                               \
    "\tbt avrcp get_remote_cap\n"                                                                                      \
    "\tbt avrcp set_local_cap [1 ~ 13]\n"                                                                              \
    "\tbt avrcp notify_vol [0 ~ 127]\n"

#define CMD_HFP_HELP_INFO                                                                                              \
    "\n\tbt hfp init\n"                                                                                                \
    "\tbt hfp connect|disconnect <mac>\n"                                                                              \
    "\tbt hfp audio_connect|audio_disconnect <mac>\n"                                                                  \
    "\tbt hfp chld [chld] [idx]\n"                                                                                     \
    "\tbt hfp answer\n"                                                                                                \
    "\tbt hfp reject\n"                                                                                                \
    "\tbt hfp dial <number>\n"                                                                                         \
    "\tbt hfp vol_update <target:[0/1]> <volume>\n"

#define CMD_A2DP_HELP_INFO "bt a2dp <sink_init|connect|disconnect> <mac_addr>\n"

char *cli_bt_uuid_str(uuid_t *uuid)
{
    static char uuid_str[37];
    uint32_t    tmp1, tmp5;
    uint16_t    tmp0, tmp2, tmp3, tmp4;

    switch (uuid->type) {
        case UUID_TYPE_16:
            snprintf(uuid_str, 37, "%04x", UUID16(uuid));
            break;

        case UUID_TYPE_32:
            snprintf(uuid_str, 37, "%04x", UUID32(uuid));
            break;

        case UUID_TYPE_128:
            memcpy(&tmp0, &UUID128(uuid)[0], sizeof(tmp0));
            memcpy(&tmp1, &UUID128(uuid)[2], sizeof(tmp1));
            memcpy(&tmp2, &UUID128(uuid)[6], sizeof(tmp2));
            memcpy(&tmp3, &UUID128(uuid)[8], sizeof(tmp3));
            memcpy(&tmp4, &UUID128(uuid)[10], sizeof(tmp4));
            memcpy(&tmp5, &UUID128(uuid)[12], sizeof(tmp5));

            snprintf(uuid_str, 37, "%08x-%04x-%04x-%04x-%08x%04x", tmp5, tmp4, tmp3, tmp2, tmp1, tmp0);
            break;

        default:
            memset(uuid_str, 0, 37);
    }

    return uuid_str;
}

const char *cli_bt_hex(const void *buf, size_t len)
{
    static const char hex[] = "0123456789abcdef";
    static char       str[129];
    const uint8_t *      b = buf;
    size_t            i;

    len = BLE_MIN(len, (sizeof(str) - 1) / 2);

    for (i = 0; i < len; i++) {
        str[i * 2]     = hex[b[i] >> 4];
        str[i * 2 + 1] = hex[b[i] & 0xf];
    }

    str[i * 2] = '\0';

    return str;
}

void cli_bt_hexdump(const uint8_t *data, size_t len)
{
    int n = 0;

    while (len--) {
        if (n % 16 == 0) {
            printf("%08X ", n);
        }

        printf("%02X ", *data++);

        n++;

        if (n % 8 == 0) {
            if (n % 16 == 0) {
                printf("\n");
            } else {
                printf(" ");
            }
        }
    }

    if (n % 16) {
        printf("\n");
    }
}

int cli_bt_bt_data_parse(uint8_t *data, size_t data_len, int (*cb)(bt_data_t *data, void *arg), void *cb_arg)
{
    uint8_t * pdata = data;
    size_t    len   = data_len;
    bt_data_t ad    = { 0 };
    int       ret;

    while (len) {
        if (pdata[0] == 0) {
            return 0;
        }

        if (len < pdata[0] + 1) {
            /* invaild data */
            return -1;
        };

        ad.len = pdata[0] - 1;

        ad.type = pdata[1];

        ad.data = &pdata[2];

        if (cb) {
            ret = cb(&ad, cb_arg);

            if (ret) {
                /* break from cb */
                return 1;
            }
        }

        len -= (pdata[0] + 1);
        pdata += (pdata[0] + 1);
    }

    return 0;
}

static inline uint8_t _char_to_hex(char c)
{
    if (c >= '0' && c <= '9') {
        return (c - '0');
    } else if (c >= 'a' && c <= 'f') {
        return (c - 'a' + 10);
    } else if (c >= 'A' && c <= 'F') {
        return (c - 'A' + 10);
    } else {
        return 0xff; /* invaild */
    }
}

int cli_bt_str_to_hex(uint8_t *hex, size_t size, char *s)
{
    uint8_t i = 0;
    uint8_t h = 0;
    uint8_t l = 0;

    if (!s || !hex || !size) {
        return 0;
    }

    for (i = 0; (*s != '\0') && (i < size); i++, s += 2) {
        h = _char_to_hex(*s);
        l = _char_to_hex(*(s + 1));
        if (h > 0x0f || l > 0x0f) {
            return 0;
        }

        hex[i] = ((h & 0x0f) << 4) | (l & 0x0f);
    }

    return i;
}

static int _bt_addr_str_to_struct(const char *str, bt_dev_addr_t *addr)
{
    int     i, j;
    uint8_t tmp;

    if (strlen(str) != 17) {
        return -BT_STACK_STATUS_EINVAL;
    }

    for (i = 5, j = 1; *str != '\0'; str++, j++) {
        if (!(j % 3) && (*str != ':')) {
            return -BT_STACK_STATUS_EINVAL;
        } else if (*str == ':') {
            i--;
            continue;
        }

        addr->val[i] = addr->val[i] << 4;

        tmp = _char_to_hex(*str);
        if (tmp > 0x0f) {
            return -BT_STACK_STATUS_EINVAL;
        }

        addr->val[i] |= tmp;
    }

    return 0;
}

int cli_bt_bt_addr_str_to_struct(const char *str, const char *type, bt_dev_addr_t *addr)
{
    int err;

    err = _bt_addr_str_to_struct(str, addr);

    if (err < 0) {
        return err;
    }

    if (!strcmp(type, "public") || !strcmp(type, "(public)")) {
        addr->type = DEV_ADDR_LE_PUBLIC;
    } else if (!strcmp(type, "random") || !strcmp(type, "(random)")) {
        addr->type = DEV_ADDR_LE_RANDOM;
    } else {
        return -BT_STACK_STATUS_EINVAL;
    }

    return 0;
}

static inline const char *bt_addr_to_string(bt_dev_addr_t *addr)
{
    /* string patter(n XX:XX:XX:XX:XX:XX public/ramdon */
    static char str[30] = { 0 };

    snprintf(str, sizeof(str) - 1, "%02X:%02X:%02X:%02X:%02X:%02X", addr->val[5], addr->val[4], addr->val[3],
             addr->val[2], addr->val[1], addr->val[0]);

    return str;
}

const char *cli_bt_bt_dev_addr_to_string(bt_dev_addr_t *addr)
{
    /* string patter(n XX:XX:XX:XX:XX:XX public/ramdon */
    static char str[30] = { 0 };
    char *      type;

    if ((addr->type & 0x01) == BT_DEV_ADDR_TYPE_PUBLIC) {
        type = "public";
    } else if ((addr->type & 0x01) == BT_DEV_ADDR_TYPE_RANDOM) {
        type = "random";
    }

    snprintf(str, sizeof(str) - 1, "%02X:%02X:%02X:%02X:%02X:%02X (%s)", addr->val[5], addr->val[4], addr->val[3],
             addr->val[2], addr->val[1], addr->val[0], type);

    return str;
}

#if defined(CONFIG_BT_BREDR) && CONFIG_BT_BREDR
static void _bt_stack_event_cb(bt_stack_cb_event_t event, bt_stack_cb_param_t *param)
{
    switch (event) {
        case BT_STACK_AUTH_CMPL_EVT: {
            if (param->auth_cmpl.status) {
                CLI_BT_PRINTF("EVT", "pairing failed err %d\n", param->auth_cmpl.status);
            } else {
                CLI_BT_PRINTF("EVT", "pairing with %s success\n", bt_addr_to_string(&param->auth_cmpl.bda));
            }
            break;
        }
        case BT_STACK_PIN_REQ_EVT: {
            CLI_BT_PRINTF("EVT", "pin code%s request from %s, input `bt pin_entry %s <pin code>` to confirm\n",
                          param->pin_req.min_16_digit ? "(16 digits long)" : "", bt_addr_to_string(&param->pin_req.bda),
                          bt_addr_to_string(&param->pin_req.bda));
            break;
        }
        case BT_STACK_CFM_REQ_EVT: {
            CLI_BT_PRINTF("EVT", "passkey confirm from %s is (%d), input `bt passkey_confirm %s` to confirm\n",
                          bt_addr_to_string(&param->cfm_req.bda), param->cfm_req.num_val,
                          bt_addr_to_string(&param->cfm_req.bda));
            break;
        }
        case BT_STACK_KEY_NOTIF_EVT: {
            CLI_BT_PRINTF("EVT", "the passkey for %s is (%d), confirm in remote device\n",
                          bt_addr_to_string(&param->key_notif.bda), param->key_notif.passkey);
            break;
        }
        case BT_STACK_KEY_REQ_EVT: {
            CLI_BT_PRINTF("EVT", "passkey request from %s, input `bt passky_entry %s <passkey, 0~999999>` to confirm\n",
                          bt_addr_to_string(&param->key_req.bda), bt_addr_to_string(&param->key_req.bda));
            break;
        }
        case BT_STACK_SET_EIR_DATA_EVT: {
            break;
        }
        default: {
            CLI_BT_PRINTF("EVT", "unsupport event %d\n", event);
            break;
        }
    }
}

static void _avrcp_notify_handle(bt_prf_avrcp_rn_event_ids_t event_id, bt_prf_avrcp_rn_param_t *event_parameter)
{
    switch (event_id) {
        case BT_PRF_AVRCP_NOTIFICATION_PLAY_STATUS_CHANGE:
            CLI_BT_PRINTF("EVT", "PLAY_STATUS_CHANGE: %d", event_parameter->playback);
            break;
        case BT_PRF_AVRCP_NOTIFICATION_PLAY_POS_CHANGED:
            CLI_BT_PRINTF("EVT", "PLAY_POS_CHANGE: %d", event_parameter->play_pos);
            break;
        case BT_PRF_AVRCP_NOTIFICATION_BATTERY_STATUS_CHANGE:
            CLI_BT_PRINTF("EVT", "BATTERY_STATUS_CHANGE: %d", event_parameter->batt);
            break;
        case BT_PRF_AVRCP_NOTIFICATION_VOLUME_CHANGE:
            CLI_BT_PRINTF("EVT", "VOLUME_CHANGE: %d", event_parameter->volume);
            break;
        case BT_PRF_AVRCP_NOTIFICATION_TRACK_CHANGE:
            CLI_BT_PRINTF("EVT", "TRACK_CHANG");
            break;
        default:
            break;
    }
}

static void _arvcp_ct_handle(bt_prf_avrcp_ct_cb_event_t event, bt_prf_avrcp_ct_cb_param_t *param)
{
    uint8_t *bt_addr;
    uint16_t bits;

    switch (event) {
        case BT_PRF_AVRCP_CT_CONNECTION_STATE_EVT:
            bt_addr = param->conn_stat.peer_addr.val;
            CLI_BT_PRINTF("EVT", "CT_CONNECTION_STATE_EVT state: %d, mac %02x%02x%02x%02x%02x%02x",
                          param->conn_stat.connected, bt_addr[0], bt_addr[1], bt_addr[2], bt_addr[3], bt_addr[4],
                          bt_addr[5]);
            break;
        case BT_PRF_AVRCP_CT_PASSTHROUGH_RSP_EVT:
            CLI_BT_PRINTF("EVT", "CT_PASSTHROUGH_RSP_EV operation_id: %d, operation_state %d",
                          param->psth_rsp.operation_id, param->psth_rsp.operation_state);
            break;
        case BT_PRF_AVRCP_CT_METADATA_RSP_EVT:
            break;
        case BT_PRF_AVRCP_CT_PLAY_STATUS_RSP_EVT:
            CLI_BT_PRINTF("EVT", "PLAY_STATUS_RSP_EVT songlen: %d, song_pso: %d, play_status: %d",
                          param->get_rn_play_status_rsp.song_len, param->get_rn_play_status_rsp.song_pos,
                          param->get_rn_play_status_rsp.play_status);
            break;
        case BT_PRF_AVRCP_CT_CHANGE_NOTIFY_EVT:
            CLI_BT_PRINTF("EVT", "CT_CHANGE_NOTIFY_EVT event_id: %d", param->change_ntf.event_id);
            _avrcp_notify_handle(param->change_ntf.event_id, &param->change_ntf.event_parameter);
            break;
        case BT_PRF_AVRCP_CT_SET_ABSOLUTE_VOLUME_RSP_EVT:
            CLI_BT_PRINTF("EVT", "CT_SET_ABSOLUTE_VOLUME_RSP_EVT volume: %d", param->set_volume_rsp.volume);
            break;
        case BT_PRF_AVRCP_CT_REMOTE_FEATURES_EVT:
            break;
        case BT_PRF_AVRCP_CT_GET_RN_CAPABILITIES_RSP_EVT:
            bits = param->get_rn_caps_rsp.evt_set.bits;
            CLI_BT_PRINTF("EVT", "CT_GET_RN_CAPABILITIES_RSP_EVT evt_bitmap: %08x", bits);
            break;
        default:
            break;
    }
}

static void _avrcp_tg_handle(bt_prf_avrcp_tg_cb_event_t event, bt_prf_avrcp_tg_cb_param_t *param)
{
    uint8_t *bt_addr;

    switch (event) {
        case BT_PRF_AVRCP_TG_CONNECTION_STATE_EVT:
            bt_addr = param->conn_stat.peer_addr.val;
            CLI_BT_PRINTF("EVT", "AVRCP_TG_CONNECTION_STATE_EVT state: %d, mac %02x%02x%02x%02x%02x%02x",
                          param->conn_stat.connected, bt_addr[0], bt_addr[1], bt_addr[2], bt_addr[3], bt_addr[4],
                          bt_addr[5]);
            break;
        case BT_PRF_AVRCP_TG_PASSTHROUGH_CMD_EVT:
            CLI_BT_PRINTF("EVT", "AVRCP_TG_PASSTHROUGH_RSP_EV operation_id: %d, operation_state %d",
                          param->psth_cmd.operation_id, param->psth_cmd.operation_state);

            break;
        case BT_PRF_AVRCP_TG_REGISTER_NOTIFICATION_EVT:
            CLI_BT_PRINTF("EVT", "AVRCP_TG_CHANGE_NOTIFY_EVT event_id: %d", param->reg_ntf.event_id);
            break;
        case BT_PRF_AVRCP_TG_SET_ABSOLUTE_VOLUME_CMD_EVT:
            CLI_BT_PRINTF("EVT", "AVRCP_TG_SET_ABSOLUTE_VOLUME_RSP_EVT volume: %d", param->set_abs_vol.volume);
            break;
        case BT_PRF_AVRCP_TG_REMOTE_FEATURES_EVT:
            break;
        default:
            break;
    }
}

static void _a2dp_handle(bt_prf_a2dp_cb_event_t event, bt_prf_a2dp_cb_param_t *param)
{
    uint8_t *bt_addr;
    uint8_t *conf;

    switch (event) {
        case BT_PRF_A2DP_CONNECTION_STATE_EVT:
            bt_addr = param->conn_stat.peer_addr.val;
            CLI_BT_PRINTF("EVT", "CONNECTION_STATE_EVT %d, mac %02x%02x%02x%02x%02x%02x", param->conn_stat.state,
                          bt_addr[0], bt_addr[1], bt_addr[2], bt_addr[3], bt_addr[4], bt_addr[5]);
            break;
        case BT_PRF_A2DP_AUDIO_STATE_EVT:
            bt_addr = param->conn_stat.peer_addr.val;
            CLI_BT_PRINTF("EVT", "AUDIO_STATE_EVT %d, mac %02x%02x%02x%02x%02x%02x", param->audio_stat.state,
                          bt_addr[0], bt_addr[1], bt_addr[2], bt_addr[3], bt_addr[4], bt_addr[5]);
            break;
        case BT_PRF_A2DP_AUDIO_SBC_CFG_EVT:
            bt_addr = param->audio_cfg.peer_addr.val;
            conf    = param->audio_cfg.sbc.config;
            CLI_BT_PRINTF("EVT", "AUDIO_SBC_CFG_EVT sbc config %02x%02x, mac %02x%02x%02x%02x%02x%02x", conf[0],
                          conf[1], bt_addr[0], bt_addr[1], bt_addr[2], bt_addr[3], bt_addr[4], bt_addr[5]);
            break;
    }
}

#endif /* CONFIG_BT_BREDR */

static void cmd_bt_stack_init(char *wbuf, int wbuf_len, int argc, char **argv)
{
    int ret;

#if defined(CONFIG_BT_BREDR) && CONFIG_BT_BREDR
    static bt_stack_cb_t bt_stack_cb = {
        .callback = _bt_stack_event_cb,
    };

    bt_stack_register_callback(&bt_stack_cb);
#endif

    ret = bt_stack_init();
    if (ret) {
        CLI_BT_PRINTF_E("bt_stack_init err %d\n", ret);
    } else {
        CLI_BT_PRINTF_I("bt_stack_init init success\n");
    }
}

static void cmd_bt_stack_set_name(char *wbuf, int wbuf_len, int argc, char **argv)
{
    int ret;

    if (argc < 2) {
        return;
    }

    ret = bt_stack_set_name(argv[1]);
    if (ret) {
        CLI_BT_PRINTF_E("set name err %d\n", ret);
        return;
    }

    CLI_BT_PRINTF_I("set name: %s success\n", argv[1]);
}

static void cmd_bt_stack_set_io_capability(char *wbuf, int wbuf_len, int argc, char **argv)
{
    int               ret;
    bt_stack_io_cap_t io_cap;

    if (argc < 2) {
        CLI_BT_PRINTF_E(CMD_SET_IO_HELP_INFO);
        return;
    }

    if (!strcmp(argv[1], "DisplayOnly")) {
        io_cap = BT_STACK_IO_CAP_OUT;
    } else if (!strcmp(argv[1], "DisplayYesNo")) {
        io_cap = BT_STACK_IO_CAP_IO;
    } else if (!strcmp(argv[1], "KeyboardOnly")) {
        io_cap = BT_STACK_IO_CAP_IN;
    } else if (!strcmp(argv[1], "None")) {
        io_cap = BT_STACK_IO_CAP_NONE;
    } else if (!strcmp(argv[1], "KeyboardDisplay")) {
        io_cap = BT_STACK_IO_CAP_IO_KEYBOARD_DISPLAY;
    } else {
        CLI_BT_PRINTF_E("unsupport param %s\n", argv[1]);
        return;
    }

    ret = bt_stack_set_io_capability(io_cap);
    if (ret) {
        CLI_BT_PRINTF_E("set io capability err %d\n", ret);
        return;
    }

    CLI_BT_PRINTF_I("set io capability %s\n", argv[1]);
}

static void cmd_bt_stack_dev_unpair(char *wbuf, int wbuf_len, int argc, char **argv)
{
    int           ret;
    bt_dev_addr_t addr = { 0 };

    if (argc < 2) {
        CLI_BT_PRINTF_E(CMD_UNPAIR_HELP_INFO);
        return;
    }

    if (argc == 2 && (!strcmp(argv[1], "All") || !strcmp(argv[1], "all"))) {
        ret = bt_stack_dev_unpair(NULL);
        if (ret) {
            CLI_BT_PRINTF_E("device unpaired err %d\n", ret);
            return;
        }

        CLI_BT_PRINTF_I("all device unparied\n");
        return;
    }

    if (argc == 3) {
        ret = cli_bt_bt_addr_str_to_struct(argv[1], argv[2], &addr);
        if (ret) {
            CLI_BT_PRINTF_E("invaild bt address %s %s\n", argv[1], argv[2]);
            return;
        }

        ret = bt_stack_dev_unpair(&addr);
        if (ret) {
            CLI_BT_PRINTF_E("device %s %s unpaired err %d\n", argv[1], argv[2], ret);
            return;
        }

        CLI_BT_PRINTF_I("device %s %s unpaired success\n", argv[1], argv[2]);

        return;
    }

    CLI_BT_PRINTF_E("invaild params\n");
}

static inline void paried_devcie(bt_dev_addr_t *addr, void *data)
{
    CLI_BT_PRINTF("bonded_dev", " %s\n", cli_bt_bt_dev_addr_to_string(addr));
}

static void cmd_bt_stack_paired_dev_foreach(char *wbuf, int wbuf_len, int argc, char **argv)
{
    CLI_BT_PRINTF_I("Bonded Device list:\n");
    bt_stack_paired_dev_foreach(paried_devcie, NULL);
}

#if defined(CONFIG_BT_BREDR) && CONFIG_BT_BREDR
static void cmd_bt_stack_set_connectable(char *wbuf, int wbuf_len, int argc, char **argv)
{
    int ret;
    int enable;

    if (argc < 2) {
        CLI_BT_PRINTF_E("invaild param\n");
        return;
    }

    enable = atoi(argv[1]);
    if (enable != 0 && enable != 1) {
        CLI_BT_PRINTF_E("invaild param, %s\n", argv[1]);
        return;
    }

    ret = bt_stack_set_connectable(enable);
    if (ret) {
        CLI_BT_PRINTF_E("set connectable err %d\n", ret);
        return;
    }

    CLI_BT_PRINTF_I("set connectable %s success\n", enable ? "enable" : "disable");
}

static void cmd_bt_stack_set_discoverable(char *wbuf, int wbuf_len, int argc, char **argv)
{
    int ret;
    int enable;

    if (argc < 2) {
        CLI_BT_PRINTF_E("invaild param\n");
        return;
    }

    enable = atoi(argv[1]);
    if (enable != 0 && enable != 1) {
        CLI_BT_PRINTF_E("invaild param, %s\n", argv[1]);
        return;
    }

    ret = bt_stack_set_discoverable(enable);
    if (ret) {
        CLI_BT_PRINTF_E("set discoverable err %d\n", ret);
        return;
    }

    CLI_BT_PRINTF_I("set discoverable %s success\n", enable ? "enable" : "disable");
}

static int _eir_data_set(bt_data_t *data, void *arg)
{
    bt_data_t **pbt_data = arg;

    **pbt_data = *data;

    (*pbt_data)++;

    return 0;
}

static int _eir_data_num(bt_data_t *data, void *arg)
{
    int *num = arg;

    (*num)++;

    return 0;
}

static void cmd_bt_stack_set_eir(char *wbuf, int wbuf_len, int argc, char **argv)
{
    int            ret;
    int            fec_required;
    static uint8_t eir_hex[240] = { 0 };
    int            len;
    int            num = 0;

    if (argc < 3) {
        CLI_BT_PRINTF_E("invaild param\n");
        return;
    }

    fec_required = atoi(argv[1]);
    if (fec_required != 0 && fec_required != 1) {
        CLI_BT_PRINTF_E("invaild param fec_required, %s\n", argv[1]);
        return;
    }

    if (strlen(argv[2]) % 2 || strlen(argv[2]) / 2 > sizeof(eir_hex)) {
        CLI_BT_PRINTF_E("invaild param eir_data size, %s\n", argv[2]);
        return;
    }

    len = cli_bt_str_to_hex(eir_hex, sizeof(eir_hex), argv[2]);
    if (len == 0) {
        CLI_BT_PRINTF_E("invaild param eir_data, %s\n", argv[2]);
        return;
    }

    ret = cli_bt_bt_data_parse(eir_hex, len, _eir_data_num, &num);
    if (ret < 0) {
        CLI_BT_PRINTF_E("invaild param %s\n", argv[2]);
        return;
    }

    if (num == 0) {
        CLI_BT_PRINTF_E("num is zero\n");
        return;
    }

    bt_data_t  bt_data[num];
    bt_data_t *pbt_data = bt_data;

    cli_bt_bt_data_parse((uint8_t *)eir_hex, len, _eir_data_set, &pbt_data);

    ret = bt_stack_set_eir(fec_required, bt_data, num);
    if (ret) {
        CLI_BT_PRINTF_E("set eir err %d\n", ret);
        return;
    }

    CLI_BT_PRINTF_I("set eir success\n");
}

static void cmd_bt_stack_set_cod(char *wbuf, int wbuf_len, int argc, char **argv)
{
    int            service_class;
    int            major_class;
    int            minor_class;
    bt_stack_cod_t cod;
    int            ret;

    if (argc < 4) {
        CLI_BT_PRINTF_E("invaild param\n");
        return;
    }

    service_class = atoi(argv[1]);
    major_class   = atoi(argv[2]);
    minor_class   = atoi(argv[3]);

    cod.service = service_class;
    cod.major   = major_class;
    cod.minor   = minor_class;

    ret = bt_stack_set_cod(cod);
    if (ret) {
        CLI_BT_PRINTF_E("set cod %s %s %s err %d\n", argv[1], argv[2], argv[3], ret);
        return;
    }

    CLI_BT_PRINTF_I("set cod %s %s %s succcess\n", argv[1], argv[2], argv[3]);
    return;
}

static void cmd_bt_stack_get_cod(char *wbuf, int wbuf_len, int argc, char **argv)
{
    int            ret;
    bt_stack_cod_t cod;

    ret = bt_stack_get_cod(&cod);
    if (ret) {
        CLI_BT_PRINTF_E("get cod err %d\n", ret);
        return;
    }

    CLI_BT_PRINTF_I("get cod service_class 0x%x major_class 0x%x, minor_class 0x%x succcess\n", cod.service, cod.major,
                    cod.minor);
}

#if defined(CONFIG_BT_A2DP) && CONFIG_BT_A2DP
static void cmd_avrcp_func(char *wbuf, int wbuf_len, int argc, char **argv)
{
    bt_stack_status_t       err = 0;

    if (argc < 2) {
        goto help_info;
    }

    if (0 == strcmp(argv[1], "ct_init")) {
        bt_prf_avrcp_ct_init();
        bt_prf_avrcp_ct_register_callback(_arvcp_ct_handle);
    } else if (0 == strcmp(argv[1], "register")) {
        if (argc < 3) {
            goto help_info;
        }

        int32_t event_id = atoi(argv[2]);
        if (event_id >= BT_PRF_AVRCP_NOTIFICATION_MAX_EVT || event_id < BT_PRF_AVRCP_NOTIFICATION_PLAY_STATUS_CHANGE) {
            goto help_info;
        }
        err = bt_prf_avrcp_ct_cmd_register_notification(event_id);
    } else if (0 == strcmp(argv[1], "pt")) {
        if (argc < 4) {
            goto help_info;
        }

        int32_t operation_id    = atoi(argv[2]);
        int32_t operation_state = atoi(argv[3]);
        if ((operation_id > BT_PRF_AVRCP_OP_ID_VENDOR || operation_id < BT_PRF_AVRCP_OP_ID_SELECT)
            || (operation_state != BT_PRF_AVRCP_OP_PRESSED && operation_state != BT_PRF_AVRCP_OP_RELEASED))
        {
            goto help_info;
        }
        err = bt_prf_avrcp_ct_cmd_passthrough(operation_id, operation_state);
    } else if (0 == strcmp(argv[1], "get_ps")) {
        err = bt_prf_avrcp_ct_cmd_get_play_status();
    } else if (0 == strcmp(argv[1], "set_abs_vol")) {
        if (argc < 3) {
            goto help_info;
        }

        int32_t vloume = atoi(argv[2]);
        if (vloume < 0 || vloume > 127) {
            goto help_info;
        }
        err = bt_prf_avrcp_ct_cmd_set_absolute_volume(vloume);
    } else {
        goto help_info;
    }

    if (err) {
        CLI_BT_PRINTF_I("%s err: %d\n", argv[1], err);
        return;
    }

    CLI_BT_PRINTF_I("%s success\n", argv[1]);
    return;

help_info:
    CLI_BT_PRINTF_E("%s\n", CMD_AVRCP_HELP_INFO);
}

static void cmd_a2dp_func(char *wbuf, int wbuf_len, int argc, char **argv)
{
    bt_stack_status_t err = 0;
    bt_dev_addr_t     peer_addr;

    if (argc < 2) {
        CLI_BT_PRINTF_E("%s\n", CMD_A2DP_HELP_INFO);
        return;
    }

    if (0 == strcmp(argv[1], "sink_init")) {
        bt_prf_a2dp_sink_init();
        bt_prf_a2dp_register_callback(_a2dp_handle);
    } else if (0 == strcmp(argv[1], "connect")) {
        cli_bt_bt_addr_str_to_struct(argv[2], "public", &peer_addr);
        err = bt_prf_a2dp_sink_connect(&peer_addr);
    } else if (0 == strcmp(argv[1], "disconnect")) {
        cli_bt_bt_addr_str_to_struct(argv[2], "public", &peer_addr);
        err = bt_prf_a2dp_sink_disconnect(&peer_addr);
    }

    if (err) {
        CLI_BT_PRINTF_I("%s err: %d\n", argv[1], err);
        return;
    }

    CLI_BT_PRINTF_I("%s success\n", argv[1]);
}
#endif /* CONFIG_BT_A2DP */

#if defined(CONFIG_BT_HFP_HF) && CONFIG_BT_HFP_HF
static void _hfp_handle(bt_prf_hfp_hf_cb_event_t event, bt_prf_hfp_hf_cb_param_t *param)
{
    uint8_t *bt_addr;

    switch (event) {
        case BT_PRF_HFP_HF_CONNECTION_STATE_EVT:
            bt_addr = param->conn_stat.peer_addr.val;
            CLI_BT_PRINTF("EVT",
                          "HF_CONNECTION_STATE_EVT %d, peer_feat: %x, chld_feat %x, mac %02x%02x%02x%02x%02x%02x",
                          param->conn_stat.state, param->conn_stat.peer_feat, param->conn_stat.chld_feat, bt_addr[0],
                          bt_addr[1], bt_addr[2], bt_addr[3], bt_addr[4], bt_addr[5]);
            break;
        case BT_PRF_HFP_HF_AUDIO_STATE_EVT:
            bt_addr = param->audio_stat.peer_addr.val;
            CLI_BT_PRINTF("EVT", "HF_AUDIO_STATE_EVT %d, mac %02x%02x%02x%02x%02x%02x", param->audio_stat.state,
                          bt_addr[0], bt_addr[1], bt_addr[2], bt_addr[3], bt_addr[4], bt_addr[5]);
            break;
        case BT_PRF_HFP_HF_CIND_CALL_EVT:
            CLI_BT_PRINTF("EVT", "HF_CIND_CALL_EVT %d", param->call.status);
            break;
        case BT_PRF_HFP_HF_CIND_CALL_SETUP_EVT:
            CLI_BT_PRINTF("EVT", "HF_CIND_CALL_SETUP_EVT %d", param->call_setup.status);
            break;
        case BT_PRF_HFP_HF_CIND_CALL_HELD_EVT:
            CLI_BT_PRINTF("EVT", "HF_CIND_CALL_HELD_EVT %d", param->call_held.status);
            break;
        case BT_PRF_HFP_HF_CIND_SERVICE_AVAILABILITY_EVT:
            CLI_BT_PRINTF("EVT", "HF_CIND_SERVICE_AVAILABILITY_EVT %d", param->service_availability.status);
            break;
        case BT_PRF_HFP_HF_CLIP_EVT:
            CLI_BT_PRINTF("EVT", "HF_CLIP_EVT %s", param->clip.number);
            break;
        case BT_PRF_HFP_HF_CCWA_EVT:
            CLI_BT_PRINTF("EVT", "HF_CCWA_EVT %s", param->ccwa.number);
            break;
        case BT_PRF_HFP_HF_CLCC_EVT:
            CLI_BT_PRINTF("EVT", "HF_CLCC_EVT %s", param->clcc.number);
            break;
        case BT_PRF_HFP_HF_BSIR_EVT:
            CLI_BT_PRINTF("EVT", "HF_BSIR_EVT %d", param->bsir.state);
            break;
        case BT_PRF_HFP_HF_CIND_BATTERY_LEVEL_EVT:
            CLI_BT_PRINTF("EVT", "HF_CIND_BATTERY_LEVEL_EVT %d", param->battery_level.value);
            break;
        case BT_PRF_HFP_HF_CIND_ROAMING_STATUS_EVT:
            CLI_BT_PRINTF("EVT", "HF_CIND_ROAMING_STATUS_EVT %d", param->roaming.status);
            break;
        case BT_PRF_HFP_HF_CIND_SIGNAL_STRENGTH_EVT:
            CLI_BT_PRINTF("EVT", "HF_CIND_SIGNAL_STRENGTH_EVT %d", param->signal_strength.value);
            break;
        case BT_PRF_HFP_HF_VOLUME_CONTROL_EVT:
        case BT_PRF_HFP_HF_AT_RESPONSE_EVT:
        case BT_PRF_HFP_HF_CNUM_EVT:
        case BT_PRF_HFP_HF_BINP_EVT:
        case BT_PRF_HFP_HF_RING_IND_EVT:
        case BT_PRF_HFP_HF_COPS_CURRENT_OPERATOR_EVT:
        case BT_PRF_HFP_HF_BTRH_EVT:
        case BT_PRF_HFP_HF_BVRA_EVT:
            break;
    }
}

static void cmd_hfp_func(char *wbuf, int wbuf_len, int argc, char **argv)
{
    bt_stack_status_t err = 0;
    bt_dev_addr_t     peer_addr;

    if (argc < 2) {
        goto help_info;
    }

    if (0 == strcmp(argv[1], "init")) {
        err = bt_prf_hfp_hf_init();
        bt_prf_hfp_hf_register_callback(_hfp_handle);
    } else if (0 == strcmp(argv[1], "connect")) {
        cli_bt_bt_addr_str_to_struct(argv[2], "public", &peer_addr);
        err = bt_prf_hfp_hf_connect(&peer_addr);
    } else if (0 == strcmp(argv[1], "disconnect")) {
        cli_bt_bt_addr_str_to_struct(argv[2], "public", &peer_addr);
        err = bt_prf_hfp_hf_disconnect(&peer_addr);
    } else if (0 == strcmp(argv[1], "audio_connect")) {
        cli_bt_bt_addr_str_to_struct(argv[2], "public", &peer_addr);
        err = bt_prf_hfp_hf_audio_connect(&peer_addr);
    } else if (0 == strcmp(argv[1], "audio_disconnect")) {
        cli_bt_bt_addr_str_to_struct(argv[2], "public", &peer_addr);
        err = bt_prf_hfp_hf_audio_disconnect(&peer_addr);
    } else if (0 == strcmp(argv[1], "chld")) {
        err = bt_prf_hfp_hf_send_chld_cmd(atoi(argv[2]), atoi(argv[3]));
    } else if (0 == strcmp(argv[1], "answer")) {
        err = bt_prf_hfp_hf_answer_call();
    } else if (0 == strcmp(argv[1], "reject")) {
        err = bt_prf_hfp_hf_reject_call();
    } else if (0 == strcmp(argv[1], "dial")) {
        bt_prf_hfp_hf_dial(argv[2]);
    } else if (0 == strcmp(argv[1], "vol_update")) {
        bt_prf_hfp_hf_vol_update(atoi(argv[2]), atoi(argv[3]));
    } else {
        goto help_info;
    }

    if (err) {
        CLI_BT_PRINTF_I("%s err: %d\n", argv[1], err);
        return;
    }

    CLI_BT_PRINTF_I("%s success\n", argv[1]);
    return;

help_info:
    CLI_BT_PRINTF_E("%s\n", CMD_AVRCP_HELP_INFO);
}
#endif

#endif /* CONFIG_BT_BREDR */

static const struct cli_command bt_cmd_info[]
    = { { "init", "bt init", cmd_bt_stack_init },
        { "set-name", "bt set-name [name]", cmd_bt_stack_set_name },
        { "set-io", CMD_SET_IO_HELP_INFO, cmd_bt_stack_set_io_capability },
        { "unpair-dev", CMD_UNPAIR_HELP_INFO, cmd_bt_stack_dev_unpair },
        { "bonded-dev", "bt bonded-dev", cmd_bt_stack_paired_dev_foreach },
#if defined(CONFIG_BT_BREDR) && CONFIG_BT_BREDR
        { "set-connectable", "bt set-connectable <enable:(0, 1)>", cmd_bt_stack_set_connectable },
        { "set-discoverable", "bt set-discoverable <enable:(0, 1)>", cmd_bt_stack_set_discoverable },
        { "set-eir", CMD_SET_EIR_HELP_INFO, cmd_bt_stack_set_eir },
        { "set-cod", "bt set-cod <service> <major> <minor>", cmd_bt_stack_set_cod },
        { "get-cod", "bt get-cod", cmd_bt_stack_get_cod },
#if defined(CONFIG_BT_A2DP) && CONFIG_BT_A2DP
        { "avrcp", CMD_AVRCP_HELP_INFO, cmd_avrcp_func },
        { "a2dp", CMD_A2DP_HELP_INFO, cmd_a2dp_func },
#endif
#if defined(CONFIG_BT_HFP_HF) && CONFIG_BT_HFP_HF
        { "hfp", CMD_HFP_HELP_INFO, cmd_hfp_func },
#endif
#endif
        { NULL, NULL, NULL } };

static void cmd_bt_func(char *wbuf, int wbuf_len, int argc, char **argv)
{
    int i = 0;

    if (argc < 2) {
        printf("================BT Command List================\n");

        for (i = 0; bt_cmd_info[i].name != NULL; i++) {
            printf("%-18s: %s\n", bt_cmd_info[i].name, bt_cmd_info[i].help);
        }

        return;
    }

    for (i = 0; bt_cmd_info[i].name != NULL; i++) {
        if (strlen(bt_cmd_info[i].name) == strlen(argv[1])
            && !strncmp(bt_cmd_info[i].name, argv[1], strlen(bt_cmd_info[i].name)))
        {
            if (bt_cmd_info[i].function) {
                bt_cmd_info[i].function(wbuf, wbuf_len, argc - 1, &argv[1]);
                return;
            }
        }
    }

    printf("Unsupport BT Command, type `bt` for help\n");
}

void cli_reg_cmd_bt_stack(void)
{
    static const struct cli_command cmd_info = {
        "bt",
        "bt <commands> [args]",
        cmd_bt_func,
    };

    aos_cli_register_command(&cmd_info);
}
#endif
