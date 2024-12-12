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

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>

#ifndef SEMI_CHECK_RET_WITH_GOTO
#define SEMI_CHECK_RET_WITH_GOTO(x, label) \
	do { \
		if (!(x)) { \
			printf("func[%s], line[%d] fail.\r\n", __FUNCTION__, __LINE__); \
			goto label; \
		}\
	} while (0)
#endif

int example_semihost(void)
{
    int rc;
    FILE *fp;
    size_t read;
    struct stat sb;
    uint8_t r_buffer[16];
    uint8_t w_buffer[16] = { 1, 2, 3, 4, 5 };
    const char *test_file = "./semihost_test.txt";

    printf("output by printf\n");
    dprintf(STDOUT_FILENO, "output by dprintf\n");
    rc = write(STDOUT_FILENO, "output by write\n", 16);
    SEMI_CHECK_RET_WITH_GOTO(rc == 16, error);

    printf("file r/w test for %s\n", test_file);
    rc = stat(test_file, &sb);
    if (rc == 0 && sb.st_size) {
        printf("File may be not empty, size = %d\r\n", (int)sb.st_size);
        goto error;
    }
    /* Open in write mode */
    fp = fopen(test_file, "w+");
    SEMI_CHECK_RET_WITH_GOTO(fp, error);

    /* Write some data */
    rc = fwrite(w_buffer, 1, sizeof(w_buffer), fp);
    SEMI_CHECK_RET_WITH_GOTO(rc == sizeof(w_buffer), error);
    rc = fwrite(w_buffer, 1, sizeof(w_buffer), fp);
    SEMI_CHECK_RET_WITH_GOTO(rc == sizeof(w_buffer), error);
    rc = (int)ftell(fp);
    SEMI_CHECK_RET_WITH_GOTO(rc == 2 * sizeof(w_buffer), error);

    /* Close the file */
    rc = fclose(fp);
    SEMI_CHECK_RET_WITH_GOTO(rc == 0, error);

    /* Open the same file again for reading */
    fp = fopen(test_file, "r");
    SEMI_CHECK_RET_WITH_GOTO(fp, error);
    fseek(fp, 0, SEEK_END);
    rc = (int)ftell(fp);
    SEMI_CHECK_RET_WITH_GOTO(rc == 2 * sizeof(w_buffer), error);
    fseek(fp, 0, SEEK_SET);

    /* Check reading data */
    read = fread(r_buffer, 1, sizeof(r_buffer), fp);
    SEMI_CHECK_RET_WITH_GOTO(read == sizeof(r_buffer), error);
    rc = memcmp(r_buffer, w_buffer, sizeof(r_buffer));
    SEMI_CHECK_RET_WITH_GOTO(rc == 0, error);
    read = fread(r_buffer, 1, sizeof(r_buffer), fp);
    SEMI_CHECK_RET_WITH_GOTO(read == sizeof(r_buffer), error);
    rc = memcmp(r_buffer, w_buffer, sizeof(r_buffer));
    SEMI_CHECK_RET_WITH_GOTO(rc == 0, error);

    /* Seek to file offset */
    fseek(fp, 1, SEEK_SET);
    SEMI_CHECK_RET_WITH_GOTO(rc == 0, error);

    /* Read from offset */
    read = fread(r_buffer, 1, sizeof(r_buffer) - 1, fp);
    SEMI_CHECK_RET_WITH_GOTO(read == sizeof(r_buffer) - 1, error);
    rc = memcmp(r_buffer, w_buffer + 1, sizeof(r_buffer) - 1);
    SEMI_CHECK_RET_WITH_GOTO(rc == 0, error);

    /* Close the file */
    rc = fclose(fp);
    SEMI_CHECK_RET_WITH_GOTO(rc == 0, error);

    /* Opening again in write mode should erase the file */
    fp = fopen(test_file, "w+");
    SEMI_CHECK_RET_WITH_GOTO(fp, error);
    rc = fclose(fp);
    SEMI_CHECK_RET_WITH_GOTO(rc == 0, error);

    printf("bare_semihost demo runs successfully!\n");
    return 0;
error:
    printf("bare_semihost demo runs fail!\n");
    return -1;
}

