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

#ifndef MQTTPUBLISH_H_
#define MQTTPUBLISH_H_

#if !defined(DLLImport)
    #define DLLImport
#endif
#if !defined(DLLExport)
    #define DLLExport
#endif

DLLExport int MQTTSerialize_publish(unsigned char *buf, int buflen, unsigned char dup, int qos, unsigned char retained,
                                    unsigned short packetid,
                                    MQTTString topicName, unsigned char *payload, int payloadlen);

DLLExport int MQTTDeserialize_publish(unsigned char *dup, int *qos, unsigned char *retained, unsigned short *packetid,
                                      MQTTString *topicName,
                                      unsigned char **payload, int *payloadlen, unsigned char *buf, int len);

// DLLExport int MQTTSerialize_puback(unsigned char* buf, int buflen, unsigned short packetid);
DLLExport int MQTTSerialize_pubrel(unsigned char *buf, int buflen, unsigned char dup, unsigned short packetid);
DLLExport int MQTTSerialize_pubcomp(unsigned char *buf, int buflen, unsigned short packetid);

#endif /* MQTTPUBLISH_H_ */
