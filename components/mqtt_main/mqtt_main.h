/* MQTT over SSL Example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#pragma once
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include "esp_system.h"
#include "nvs_flash.h"
#include "esp_event.h"
#include "esp_netif.h"

#include "esp_log.h"
#include "mqtt_client.h"
#include "esp_tls.h"
#include "esp_ota_ops.h"

//#include <bmp280_main.h>
#include <hallsensor_main.h>
#include <rtos_define.h>


#define MQTT_BROKER_URI CONFIG_MQTT_BROKER_URI
#define MQTT_BROKER_TOPIC CONFIG_MQTT_BROKER_TOPIC

extern const uint8_t ca_crt_start[]   asm("_binary_ca_crt_start");
extern const uint8_t ca_crt_end[]   asm("_binary_ca_crt_end");

static void send_binary(esp_mqtt_client_handle_t client);

static esp_err_t mqtt_event_handler_cb(esp_mqtt_event_handle_t event);

static void mqtt_event_handler(void *handler_args, esp_event_base_t base, int32_t event_id, void *event_data);

void rtos_wait_forever();

static void mqtt_app_start(void *pvParameter);

void start_mqtt(void);
