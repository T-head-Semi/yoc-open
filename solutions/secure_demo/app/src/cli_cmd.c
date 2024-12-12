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
#include <aos/cli.h>
#include "app_main.h"

void se_test_register_cmd(void);

void board_cli_init()
{
    aos_cli_init();

    extern void cli_reg_cmd_ps(void);
    cli_reg_cmd_ps();

    extern void cli_reg_cmd_free(void);
    cli_reg_cmd_free();

    se_test_register_cmd();

}

extern void se_drv_init_by_cmd(void);
static void secure_test_register_se_init_main(char *pcWriteBuffer, int xWriteBufferLen, int argc, char **argv)
{
    se_drv_init_by_cmd();
}


extern void secure_sc_test_main(void);
static void secure_test_register_sc_main(char *pcWriteBuffer, int xWriteBufferLen, int argc, char **argv)
{
    secure_sc_test_main();
}

extern void secure_se_test_main(void);
static void secure_test_register_se_main(char *pcWriteBuffer, int xWriteBufferLen, int argc, char **argv)
{
    secure_se_test_main();
}

extern void se_test_device_by_cmd(void);
static void secure_test_register_firm_update_main(char *pcWriteBuffer, int xWriteBufferLen, int argc, char **argv)
{
    se_test_device_by_cmd();
}

extern void se_import_root_key_by_cmd(void);
static void secure_test_register_root_key_main(char *pcWriteBuffer, int xWriteBufferLen, int argc, char **argv)
{
    se_import_root_key_by_cmd();
}

extern void se_import_aes_key_by_cmd(void);
static void secure_test_register_aes_key_main(char *pcWriteBuffer, int xWriteBufferLen, int argc, char **argv)
{
    se_import_aes_key_by_cmd();
}

extern void set_test_rsa1024_import_sbootkey_by_cmd(void);
static void secure_test_register_sboot_rsa1024_main(char *pcWriteBuffer, int xWriteBufferLen, int argc, char **argv)
{
    set_test_rsa1024_import_sbootkey_by_cmd();
}

extern void set_test_rsa1024_import_keypair_by_cmd(void);
static void secure_test_register_rsa1024_keypair_main(char *pcWriteBuffer, int xWriteBufferLen, int argc, char **argv)
{
    set_test_rsa1024_import_keypair_by_cmd();
}

extern void set_test_rsa2048_import_keypair_by_cmd(void);
static void secure_test_register_rsa2048_keypair_main(char *pcWriteBuffer, int xWriteBufferLen, int argc, char **argv)
{
    set_test_rsa2048_import_keypair_by_cmd();
}

extern void se_test_rsa1024_import_pubkey_by_cmd(void);
static void secure_test_register_rsa1024_pubkey_main(char *pcWriteBuffer, int xWriteBufferLen, int argc, char **argv)
{
    se_test_rsa1024_import_pubkey_by_cmd();
}

extern void se_test_rsa2048_import_pubkey_by_cmd(void);
static void secure_test_register_rsa2048_pubkey_main(char *pcWriteBuffer, int xWriteBufferLen, int argc, char **argv)
{
    se_test_rsa2048_import_pubkey_by_cmd();
}

void se_test_register_cmd(void)
{
    static struct cli_command cmd_infos[] = {
        {
            "se_drv_init",
            "update se firm and read current version",
            secure_test_register_se_init_main,
        },
        {
            "se_import_rootkey",
            "root key and encrypt key import",
            secure_test_register_root_key_main,
        },
        {
            "se_import_aeskey",
            "aes 128 and 192 and 256 key import",
            secure_test_register_aes_key_main,
        },
        {
            "se_import_rsa1024_sbootkey",
            "rsa 1024 public key for secure boot",
            secure_test_register_sboot_rsa1024_main,
        },
        {
            "se_import_rsa1024_keypair",
            "rsa 1024 keypair ND and CRT format import",
            secure_test_register_rsa1024_keypair_main,
        },
        {
            "se_import_rsa2048_keypair",
            "rsa 2048 keypair ND and CRT format import",
            secure_test_register_rsa2048_keypair_main,
        },
        {
            "se_import_rsa1024_pubkey",
            "rsa 1024 only public key import",
            secure_test_register_rsa1024_pubkey_main,
        },
        {
            "se_import_rsa2048_pubkey",
            "rsa 2048 only public key import",
            secure_test_register_rsa2048_pubkey_main,
        },
        {
            "se_update_firm",
            "update se firm and read current version",
            secure_test_register_firm_update_main
        },
        {
            "se_test_all",
            "test se all security algorithm function",
            secure_test_register_se_main
        },
        {
            "sc_test_all",
            "test se all security algorithm function",
            secure_test_register_sc_main
        },
    };

    aos_cli_register_commands(cmd_infos, sizeof(cmd_infos)/sizeof(struct cli_command));
}
