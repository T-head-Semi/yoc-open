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

#ifndef __TS_MUXER_HPP__
#define __TS_MUXER_HPP__

#include <mpegts/ts_typedef.h>
#include <mpegts/ts_frame.hpp>
#include <mpegts/ts_format.hpp>
#include <mpegts/bytes_io.hpp>
#include <memory>
#include <map>
using namespace std;
#define PSI_INTERVAL_DEFAULT           (15)

class TsMuxer
{
public:
    TsMuxer();
    ~TsMuxer();

    /**
     * @brief  add one pmt table
     * @param  [in] pid : pid of the pmt table(0x10~0x1ffe)
     * @return 0/-1
     */
    void         addPmt(uint16_t pid);

    /**
     * @brief  add track-element info of the pmt
     * @param  [in] pid_pmt(0x10~0x1ffe)
     * @param  [in] type
     * @param  [in] pid : pid of the track-element(0x10~0x1ffe)
     * @return 0/-1
     */
    void         addPmtElement(uint16_t pid_pmt, ES_TYPE_ID type, uint16_t pid);

    /**
     * @brief  pack the frame
     * @param  [in] frame : audio or video frame data
     * @return 0/-1
     */
    int          pack(const TsFrame *frame);
    void         reset();
    uint8_t      *data();
    size_t       size();

private:
    /**
     * @brief  get countinue counter of the pid
     * @param  [in] pid
     * @return 0x0~0xf
     */
    uint8_t     _getCC(uint16_t pid);   //get countinue counter of the pid

    /**
     * @brief  pack pat of psi
     * @return
     */
    void        _packPat();  //pack pat of psi

    /**
    * @brief  pack pmt of psi
    * @return
    */
    void        _packPmt();   //pack pmt of psi

    /**
     * @brief  pack one pes of the frame
     * @param  [in] frame : audio or video frame data
     * @return
     */
    void        _packPes(const TsFrame *frame);  //pack one pes of the frame, [in] frame : audio or video frame data

    uint16_t                                         _mPcrPid;
    uint8_t                                          _mPsiInterval;
    uint8_t                                          _mPsiCurInterval;
    BytesIO                                         *_mIO;
    void                                            *_mUserData;
    map<uint16_t, vector<shared_ptr<PmtElement>>>    _mPmtInfo;
    map<uint16_t, uint8_t>                           _mPidCC;
};

#endif
