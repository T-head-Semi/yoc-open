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

#ifndef __TS_FRAME_HPP__
#define __TS_FRAME_HPP__

#include <mpegts/ts_typedef.h>

class TsFrame
{
    friend class TsMuxer;

public:
    TsFrame();

public:
    void         reset();
    void         setFrame(const uint8_t *data, size_t size);
    void         setTimestamp(uint64_t pts, uint64_t dts);
    void         setPid(uint16_t pid);
    void         setType(ES_TYPE_ID type);
    bool         frame_setted() const;

private:
    uint8_t      *_mData;
    size_t       _mSize;
    uint64_t     _mPts;
    uint64_t     _mDts;
    //uint64_t     _mPcr;
    ES_TYPE_ID    _mType;
    uint16_t     _mPid;
};
#endif
