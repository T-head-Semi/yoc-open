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



#ifndef __IOT_IMPORT_CONFIG_H__
#define __IOT_IMPORT_CONFIG_H__

#ifndef CONFIG_HTTP_AUTH_TIMEOUT
    #define CONFIG_HTTP_AUTH_TIMEOUT        (5 * 1000)
#endif

#ifndef CONFIG_MID_HTTP_TIMEOUT
    #define CONFIG_MID_HTTP_TIMEOUT         (5 * 1000)
#endif

#ifndef CONFIG_GUIDER_AUTH_TIMEOUT
    #define CONFIG_GUIDER_AUTH_TIMEOUT      (10 * 1000)
#endif

#ifndef CONFIG_COAP_AUTH_TIMEOUT
    #define CONFIG_COAP_AUTH_TIMEOUT        (3 * 1000)
#endif

#ifndef CONFIG_MQTT_TX_MAXLEN
	#ifndef LINK_VISUAL_ENABLE
    #define CONFIG_MQTT_TX_MAXLEN           (2048)
	#else
	    #define CONFIG_MQTT_TX_MAXLEN           (16*1024)
	#endif
#endif

#ifndef CONFIG_MQTT_RX_MAXLEN
	#ifndef LINK_VISUAL_ENABLE
    #define CONFIG_MQTT_RX_MAXLEN           (2048)
	#else
	    #define CONFIG_MQTT_RX_MAXLEN           (16*1024)
	#endif
#endif

#ifndef CONFIG_SDK_THREAD_COST
    #define CONFIG_SDK_THREAD_COST          (0)
#endif

#ifndef CONFIG_MBEDTLS_DEBUG_LEVEL
    #define CONFIG_MBEDTLS_DEBUG_LEVEL      (0)
#endif

#ifndef CONFIG_RUNTIME_LOG_LEVEL
    #define CONFIG_RUNTIME_LOG_LEVEL        (5)
#endif

#ifndef CONFIG_BLDTIME_MUTE_DBGLOG
    #define CONFIG_BLDTIME_MUTE_DBGLOG      (1)
#endif

#ifndef CONFIG_DISPATCH_QUEUE_MAXLEN
    #ifndef LINK_VISUAL_ENABLE
    #define CONFIG_DISPATCH_QUEUE_MAXLEN    (20)
    #else
    #define CONFIG_DISPATCH_QUEUE_MAXLEN    (160)
    #endif
#endif

#ifndef CONFIG_DISPATCH_PACKET_MAXCOUNT
    #define CONFIG_DISPATCH_PACKET_MAXCOUNT (0)
#endif

#ifndef CONFIG_MSGCACHE_QUEUE_MAXLEN
    #define CONFIG_MSGCACHE_QUEUE_MAXLEN    (20)
#endif

#endif  /* __IOT_IMPORT_CONFIG_H__ */
