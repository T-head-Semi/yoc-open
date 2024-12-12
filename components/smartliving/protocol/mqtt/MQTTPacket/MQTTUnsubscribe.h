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

#ifndef MQTTUNSUBSCRIBE_H_
#define MQTTUNSUBSCRIBE_H_

#if !defined(DLLImport)
  #define DLLImport 
#endif
#if !defined(DLLExport)
  #define DLLExport
#endif

DLLExport int MQTTSerialize_unsubscribe(unsigned char* buf, int buflen, unsigned char dup, unsigned short packetid,
		int count, MQTTString topicFilters[]);

DLLExport int MQTTDeserialize_unsubscribe(unsigned char* dup, unsigned short* packetid, int max_count, int* count, MQTTString topicFilters[],
		unsigned char* buf, int len);

DLLExport int MQTTSerialize_unsuback(unsigned char* buf, int buflen, unsigned short packetid);

DLLExport int MQTTDeserialize_unsuback(unsigned short* packetid, unsigned char* buf, int len);

#endif /* MQTTUNSUBSCRIBE_H_ */
