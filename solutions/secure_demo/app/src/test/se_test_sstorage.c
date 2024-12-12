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
#include <string.h>
#include <se_device.h>
#include <se_rng.h>
#include <se_storage.h>
#include "yunit.h"


static void se_test_sstorage_demo(void)
{
    int ret = 0;
	uint32_t size;
	uint8_t *buf;
	uint8_t *buf1;
	uint32_t pos;
	uint32_t test_len;

	/* Get the capacity of secure storage */
	ret = se_get_avail_storage_capacity(&size);
    YUNIT_ASSERT_MSG_QA(ret == 0, "the se_get_avail_storage_capacity test is %d", ret);
	printf("The size of secure storage is: 0x%x\r\n", size);

	/* malloc buffer */
	buf = malloc(size);
    YUNIT_ASSERT_MSG_QA(buf != 0, "the malloc buffer failed");
	buf1 = malloc(size);
    YUNIT_ASSERT_MSG_QA(buf != 0, "the malloc buffer failed");

	/* Initialize test data */
    ret = se_rng_get_bytes(buf, size);
    YUNIT_ASSERT_MSG_QA(ret == 0, "the se_rng_get_bytes test get 32bytes is %d", ret);

	/* Test API */
	for (pos = 0; pos < size; pos++) {
		test_len = size - pos;
		ret = se_write_storage_data((const uint8_t *)buf, test_len, pos);
   	 	YUNIT_ASSERT_MSG_QA(ret == 0, "the se_write_storage_data test is %d @pos:%d", ret, pos);
		
		ret = se_read_storage_data(buf1, test_len, pos);
   	 	YUNIT_ASSERT_MSG_QA(ret == 0, "the se_write_storage_data test is %d @pos:%d", ret, pos);

		ret = memcmp(buf, buf1, test_len);
    	YUNIT_ASSERT_MSG_QA(ret == 0, "the secure storage read back check failed is %d", ret);
	}

	if (buf) {
		free(buf);
		buf = NULL;
	}
	if (buf1) {
		free(buf);
		buf1 = NULL;
	}
}

void se_test_sstorage(void)
{
    /***************RNG TEST START****************/

    add_yunit_test("sstorage", &se_test_sstorage_demo);

    /***************RNG TEST END****************/
}

