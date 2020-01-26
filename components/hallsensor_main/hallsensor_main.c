#include "hallsensor_main.h"

static const char *TAG = "hallsensor_main";

void hallsensor_main(void *pvParameter)
{
    int msg_id;
    char sensor_values[128];
    adc1_config_width(ADC_WIDTH_BIT_12);
    while (1)
    {
        vTaskDelay(500 / portTICK_PERIOD_MS);
	int hall_value = hall_sensor_read();
        snprintf(sensor_values, sizeof(sensor_values), "Hallsensor: %d", hall_value);
        printf("%s\n", sensor_values);
        msg_id = esp_mqtt_client_publish(pvParameter, MQTT_BROKER_TOPIC, sensor_values, 0, 0, 0);
	if(diagnostic_is_ok == false){
		diagnostic();
	}
        ESP_LOGD(TAG, "@doc Wait 5sec at the end of the while(1)");
        vTaskDelay(RTOS_DELAY_5SEC);
    }
}


void read_hall(esp_mqtt_client_handle_t client){
    BaseType_t xReturned;

    xReturned = xTaskCreatePinnedToCore(hallsensor_main, "hallsensor_main", MYAPP_RTOS_TASK_STACK_SIZE_LARGE, client, RTOS_TASK_PRIORITY_NORMAL, NULL, 1);
    if (xReturned == pdPASS) {
        printf("OK Task hallsensor_main has been created, and is running right now\n");
    }
}
