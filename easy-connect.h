/*
 * FILE: easy-connect.h
 *
 * Copyright (c) 2015 - 2017 ARM Limited. All rights reserved.
 * SPDX-License-Identifier: Apache-2.0
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#ifndef __EASY_CONNECT_H__
#define __EASY_CONNECT_H__

#include "mbed.h"

#define ETHERNET          1
#define WIFI_ESP8266      11
#define WIFI_ODIN         12
#define WIFI_RTW          13
#define WIFI_IDW0XX1      14
#define MESH_LOWPAN_ND    101
#define MESH_THREAD       102
#define CELLULAR_ONBOARD  201

/* Define supersets for WiFi and Mesh */

#if MBED_CONF_APP_NETWORK_INTERFACE == WIFI_ESP8266
#define WIFI

#elif MBED_CONF_APP_NETWORK_INTERFACE == WIFI_ODIN
#define WIFI

#elif MBED_CONF_APP_NETWORK_INTERFACE == WIFI_RTW
#define WIFI

#elif MBED_CONF_APP_NETWORK_INTERFACE == WIFI_IDW0XX1
#define WIFI

#elif MBED_CONF_APP_NETWORK_INTERFACE == MESH_LOWPAN_ND
#define MESH

#elif MBED_CONF_APP_NETWORK_INTERFACE == MESH_THREAD
#define MESH
#endif // MBED_CONF_APP_NETWORK_INTERFACE

#if defined(MESH)

// Define macros for radio type
#define ATMEL   1
#define MCR20   2
#define SPIRIT1 3
#define EFR32   4

// This is address to mbed Device Connector (hard-coded IP due to DNS might not be there)
#define MBED_SERVER_ADDRESS "coaps://[2607:f0d0:2601:52::20]:5684"

#else
// This is address to mbed Device Connector
#define MBED_SERVER_ADDRESS "coap://api.connector.mbed.com:5684"

#endif // (MESH)

// In case the mbed_app.json only defined WIFI SSID/PASSWORD, not ESP8266 ones.
#if not defined MBED_CONF_APP_ESP8266_SSID
#define MBED_CONF_APP_ESP8266_SSID         MBED_CONF_APP_WIFI_SSID
#else
#define MBED_CONF_APP_WIFI_PASSWORD        MBED_CONF_APP_ESP8266_PASSWORD
#endif

#if not defined MBED_CONF_APP_ESP8266_PASSWORD
#define MBED_CONF_APP_ESP8266_PASSWORD     MBED_CONF_APP_WIFI_PASSWORD
#else
#define MBED_CONF_APP_WIFI_SSID            MBED_CONF_APP_ESP8266_SSID
#endif

#if not defined MBED_CONF_APP_ESP8266_TX
#define MBED_CONF_APP_ESP8266_TX         MBED_CONF_APP_WIFI_TX
#endif

#if not defined MBED_CONF_APP_ESP8266_RX
#define MBED_CONF_APP_ESP8266_RX         MBED_CONF_APP_WIFI_RX
#endif

/* \brief print_MAC - print_MAC  - helper function to print out MAC address
 * in: network_interface - pointer to network i/f
 *     bool log-messages   print out logs or not
 * MAC address is print, if it can be acquired & log_messages is true.
 *
 */
void print_MAC(NetworkInterface* network_interface, bool log_messages);


/* \brief easy_connect - easy_connect function to connect the pre-defined network bearer,
 *                       config done via mbed_app.json (see README.md for details).
 * IN: bool  log_messages  print out diagnostics or not.
 */
NetworkInterface* easy_connect(bool log_messages = false);

/* \brief easy_connect - easy_connect function to connect the pre-defined network bearer,
 *                       config done via mbed_app.json (see README.md for details).
 * IN: bool  log_messages  print out diagnostics or not.
 *     char* WiFiSSID      WiFi SSID - by default NULL, but if it's NULL
 *                         then MBED_CONF_APP_WIFI_SSID will be used
 *     char* WiFiPassword  WiFi Password - by default NULL, but if it's NULL
 *                         then MBED_CONF_APP_WIFI_PASSWORD will be used
 */
NetworkInterface* easy_connect(bool log_messages,
                               char* WiFiSSID,
                               char* WiFiPassword);
#endif // __EASY_CONNECT_H__
