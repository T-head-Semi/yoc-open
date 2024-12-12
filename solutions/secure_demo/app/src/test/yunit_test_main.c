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

#include <stdlib.h>
#include <stdio.h>
#include "yunit.h"


void yunit_test_main(void)
{
    int ret = 0;

    ret = yunit_test_run();
    printf("\nTests completed with return value %d\n", ret);

    yunit_test_print_result();

    yunit_test_deinit();
}

void add_yunit_test(const char *name, yunit_test_case_proc proc) {
    static int ini = 0;
    static yunit_test_suite_t *suite;
    if(ini == 0) {
        yunit_test_init();
	    suite = yunit_add_test_suite(name, NULL, NULL, NULL, NULL);
        ini = 1;
    }

    yunit_add_test_case(suite, name, proc);
}