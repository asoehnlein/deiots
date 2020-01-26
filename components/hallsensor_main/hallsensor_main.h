#pragma once
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include <driver/adc.h>
#include "esp_system.h"
#include "esp_log.h"

#include <rtos_define.h>
#include <mqtt_main.h>
#include <advanced_https_ota.h>

void hallsensor_main(void *pvParameter);
void read_hall(esp_mqtt_client_handle_t client);
