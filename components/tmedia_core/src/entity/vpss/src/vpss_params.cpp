/*
 * Copyright (C) 2022 Alibaba Group Holding Limited
 */

#include <iostream>

#include <tmedia_core/common/common_inc.h>
#include <tmedia_core/util/util_inc.h>

#include <tmedia_core/entity/vpss/vpss_params.h>

using namespace std;

TMVpssParams::TMVpssParams()
{
    Reset();
    mMaxWidth = 0;
    mMaxHeight = 0;
    mPixelFormat = TMImageInfo::PixelFormat::PIXEL_FORMAT_NV12;
    mDynamicRange = DYNAMIC_RANGE_SDR8;
    mFrameRate.dstFrameRate = 0;
    mFrameRate.srcFrameRate = 0;
}

void TMVpssParams::Reset()
{
}

void TMVpssParams::Dump()
{
}

