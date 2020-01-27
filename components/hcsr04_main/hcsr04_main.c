#include "hcsr04_main.h"

static const char *TAG = "hcsr04_main";

void ultrasonic_test(void *pvParameter)
{
    ultrasonic_sensor_t sensor = {
        .trigger_pin = TRIGGER_GPIO,
        .echo_pin = ECHO_GPIO
    };

    ultrasonic_init(&sensor);

    int msg_id;
    char sensor_values[128];

    while (true)
    {
        uint32_t distance;
        esp_err_t res = ultrasonic_measure_cm(&sensor, MAX_DISTANCE_CM, &distance);
        if (res != ESP_OK)
        {
            printf("Error: ");
            switch (res)
            {
                case ESP_ERR_ULTRASONIC_PING:
                    printf("Cannot ping (device is in invalid state)\n");
                    msg_id = esp_mqtt_client_publish(pvParameter, MQTT_BROKER_TOPIC, "HC-SR04 could not be pinged (invalid state), retry in 5sec", 0, 0, 0);
                    vTaskDelay(5000 / portTICK_PERIOD_MS);
                    break;
                case ESP_ERR_ULTRASONIC_PING_TIMEOUT:
                    printf("Ping timeout (no device found)\n");
                    msg_id = esp_mqtt_client_publish(pvParameter, MQTT_BROKER_TOPIC, "HC-SR04 ping timeout (no device found), retry in 5sec", 0, 0, 0);
                    vTaskDelay(5000 / portTICK_PERIOD_MS);
                    break;
                case ESP_ERR_ULTRASONIC_ECHO_TIMEOUT:
                    printf("Echo timeout (i.e. distance too big)\n");
                    msg_id = esp_mqtt_client_publish(pvParameter, MQTT_BROKER_TOPIC, "HC-SR04 echo timeout (i.e. distance too big), retry in 5sec", 0, 0, 0);
                    vTaskDelay(5000 / portTICK_PERIOD_MS);
                    break;
                default:
                    printf("%d\n", res);
            }
        }
        else{
            snprintf(sensor_values, sizeof(sensor_values), "Distance: %d cm\n", distance);
            printf("HC-SR04: %s\n", sensor_values);
            msg_id = esp_mqtt_client_publish(pvParameter, MQTT_BROKER_TOPIC, sensor_values, 0, 0, 0);
            if(diagnostic_is_ok == false){
            //    ESP_LOGI(TAG, "Setting diagnostics to true");
                diagnostic();
            }
            ESP_LOGD(TAG, "@doc Wait 5sec at the end of the while(1)");
            vTaskDelay(RTOS_DELAY_5SEC);
        }
    }
}

void start_us(esp_mqtt_client_handle_t client)
{
    BaseType_t xReturned;

// Testing OTA this will panic Core 0 after execution and will then rollback to previous version
//    xTaskCreate(ultrasonic_test, "ultrasonic_test", configMINIMAL_STACK_SIZE * 3, NULL, 5, NULL);

    ESP_LOGI(TAG, "@doc Wait 5 seconds after power-on (start logic analyzer, let sensors become active!)");
    vTaskDelay(RTOS_DELAY_5SEC);
    xReturned =xTaskCreatePinnedToCore(ultrasonic_test, "ultrasonic_test", MYAPP_RTOS_TASK_STACK_SIZE_LARGE, client, RTOS_TASK_PRIORITY_NORMAL, NULL, 1); 
    if (xReturned == pdPASS) {
        printf("OK Task ultrasonic_test has been created, and is running right now\n");
    }

    ESP_LOGI(TAG, "hcsr04() END");

}

