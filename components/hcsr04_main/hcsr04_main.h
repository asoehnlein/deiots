#pragma once
#include <stdio.h>
#include <stdbool.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <ultrasonic.h>

#include <mqtt_main.h>
#include <advanced_https_ota.h>

#define MAX_DISTANCE_CM 400 // 4m max
#define TRIGGER_GPIO CONFIG_SCL_GPIO
#define ECHO_GPIO CONFIG_SDA_GPIO

void ultrasonic_test(void *pvParameter);

void start_us(esp_mqtt_client_handle_t client);
