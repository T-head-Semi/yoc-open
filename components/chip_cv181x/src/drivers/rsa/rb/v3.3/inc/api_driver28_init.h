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
/* api_driver28_init.h
 *
 * Security-IP-28 Driver Initialization Interface
 */



#ifndef DRIVER28_INIT_H_
#define DRIVER28_INIT_H_


/*----------------------------------------------------------------------------
 * Driver28_Init
 *
 * Initialize the driver. This function must be called before any other
 * driver API function can be called.
 *
 * Returns 0 for success and -1 for failure.
 */
int
Driver28_Init(void);

/*----------------------------------------------------------------------------
 * Driver28_Exit
 *
 * Initialize the driver. After this function is called no other driver API
 * function can be called except Driver28_Init().
 */
void
Driver28_Exit(void);


#endif /* DRIVER28_INIT_H_ */

/* end of file api_driver28_init.h */
