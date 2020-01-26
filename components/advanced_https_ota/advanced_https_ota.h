/* Advanced HTTPS OTA example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#pragma once
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "esp_system.h"
#include "esp_event.h"
#include "esp_log.h"
#include "esp_ota_ops.h"
#include "esp_http_client.h"
#include "esp_https_ota.h"
#include "nvs.h"
#include "nvs_flash.h"
#include "protocol_examples_common.h"

#if CONFIG_EXAMPLE_CONNECT_WIFI
#include "esp_wifi.h"
#endif

extern const uint8_t server_cert_pem_start[] asm("_binary_ca_cert_pem_start");
extern const uint8_t server_cert_pem_end[] asm("_binary_ca_cert_pem_end");

#define HASH_LEN 32
#define BUFFSIZE 1024

static bool diagnostic_is_ok;

bool diagnostic(void);

static void print_sha256 (const uint8_t *image_hash, const char *label);

static esp_err_t validate_image_header(esp_app_desc_t *new_app_info);

void advanced_ota_example_task(void *pvParameter);

void start_ota(void);

static esp_err_t validate_image_header_firmware_check(esp_app_desc_t *new_app_info);

void check_firmware_task(void *pvParameter);

void start_firmware_check(void *pvParameter);
