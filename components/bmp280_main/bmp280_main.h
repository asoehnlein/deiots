#pragma once
#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <esp_system.h>
#include <bmp280.h>
#include <string.h>

#include <rtos_define.h>
#include <mqtt_main.h>
#include <advanced_https_ota.h>

#define SDA_GPIO CONFIG_SDA_GPIO
#define SCL_GPIO CONFIG_SCL_GPIO
#define I2C_ADDRESS CONFIG_I2C_ADDRESS

void bmp280_main(void *pvParameter);

void start_bmp280(esp_mqtt_client_handle_t client);

