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

#include "aos/integer.h"
#include "time.h"

DWORD get_fattime(void)
{
	DWORD res;
	time_t utime;
	struct tm *tm = NULL;

	time(&utime);
	tm = localtime(&utime);

	res =  (((DWORD)tm->tm_year + 1900 - 1980) << 25)
			| (((DWORD)tm->tm_mon + 1) << 21)
			| ((DWORD)tm->tm_mday << 16)
			| (WORD)(tm->tm_hour << 11)
			| (WORD)(tm->tm_min << 5)
			| (WORD)(tm->tm_sec >> 1);
	return res;
}
