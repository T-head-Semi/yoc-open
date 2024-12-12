/*
 * Copyright (C) 2017-2024 Alibaba Group Holding Limited
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef __BYTES_IO_HPP__
#define __BYTES_IO_HPP__

#include <mpegts/ts_typedef.h>
#include <vector>
using namespace std;

class BytesIO final
{
public:
    BytesIO();
    BytesIO(size_t capacity);
    ~BytesIO();

    void       w8(uint8_t val);
    void       w16be(uint16_t val);
    void       w24be(uint32_t val);
    void       w32be(uint32_t val);
    void       w64be(uint64_t val);

    size_t     size();
    uint8_t    *data();
    void       setData(const uint8_t *data, size_t len, size_t offset);
    void       append(const uint8_t *data, size_t size);
    void       append(uint8_t ch, size_t size = 1);
    void       resetCurrPos();
    int        getCurrPos();

private:
    size_t           _mPos;
    vector<uint8_t>  _mData;
    size_t           _mCurrPos;
};
#endif
