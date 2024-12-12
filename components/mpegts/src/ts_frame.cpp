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
#include <mpegts/ts_frame.hpp>

TsFrame::TsFrame()
{
    reset();
}

void TsFrame::setFrame(const uint8_t *data, size_t size)
{
    if (data && size)
    {
        _mSize = size;
        _mData = (uint8_t *)data;
    }
}

void TsFrame::setTimestamp(uint64_t pts, uint64_t dts)
{
    _mPts  = pts;
    _mDts  = dts;
    //_mPcr  = pcr;
}

void TsFrame::setPid(uint16_t pid)
{
    _mPid  = pid;
}

void TsFrame::setType(ES_TYPE_ID type)
{
    _mType = type;
}

void TsFrame::reset()
{
    _mPid  = 0;
    _mSize = 0;
    _mData = NULL;
    _mType = ES_TYPE_ID::UNKNOWN;
    _mPts  = _mDts  = 0;
    //_mPcr = 0;
}

bool  TsFrame::frame_setted() const
{
    if (_mData && _mSize && _mPid && _mType)
    {
        return true;
    }
    else
    {
        return false;
    }
}


