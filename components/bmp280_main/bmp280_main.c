#include "bmp280_main.h"

static const char *TAG = "mqtt_main";

void bmp280_main(void *pvParameter)
{
    bmp280_params_t params;
    bmp280_init_default_params(&params);
    bmp280_t dev;
    memset(&dev, 0, sizeof(bmp280_t));

    ESP_ERROR_CHECK(bmp280_init_desc(&dev, BMP280_I2C_ADDRESS_0, 0, SDA_GPIO, SCL_GPIO));
    ESP_ERROR_CHECK(bmp280_init(&dev, &params));

    bool bme280p = dev.id == BME280_CHIP_ID;
    printf("BMP280: found %s\n", bme280p ? "BME280" : "BMP280");

    float pressure, temperature, humidity;

    int msg_id;
    char sensor_values[128];

    while (1)
    {
        vTaskDelay(500 / portTICK_PERIOD_MS);
        if (bmp280_read_float(&dev, &temperature, &pressure, &humidity) != ESP_OK)
        {
            printf("Temperature/pressure reading failed\n");
            msg_id = esp_mqtt_client_publish(pvParameter, MQTT_BROKER_TOPIC, "Sensor has not been found, retry in 5sec", 0, 0, 0);
            vTaskDelay(5000 / portTICK_PERIOD_MS);
            continue;
        }

        /* float is used in printf(). you need non-default configuration in
         * sdkconfig for ESP8266, which is enabled by default for this
         * example. see sdkconfig.defaults.esp8266
         */
        snprintf(sensor_values, sizeof(sensor_values), "AirPressure %.4f HPa | Temperature %.2f *C", pressure / 100, temperature);
        printf("Sensor: %s\n", sensor_values);
        msg_id = esp_mqtt_client_publish(pvParameter, MQTT_BROKER_TOPIC, sensor_values, 0, 0, 0);
        if(diagnostic_is_ok == false){
            diagnostic();
        }
        ESP_LOGD(TAG, "@doc Wait 15sec at the end of the while(1)");
        vTaskDelay(RTOS_DELAY_15SEC);
        if (bme280p)
            printf(", Humidity: %.2f\n", humidity);
        else
            printf("\n");
    }
}

void start_bmp280(esp_mqtt_client_handle_t client)
{
    BaseType_t xReturned;

    /* SOC init */
    ESP_LOGI(TAG, "@doc exec nvs_flash_init() - mandatory for Wifi to work later on");
    nvs_flash_init();

    /* MY STANDARD Init */
    ESP_ERROR_CHECK(i2cdev_init());
    ESP_LOGI(TAG, "@doc Wait 5 seconds after power-on (start logic analyzer, let sensors become active!)");
    vTaskDelay(RTOS_DELAY_5SEC);

    /*
     * Sensor Task
     */
    xReturned = xTaskCreatePinnedToCore(bmp280_main, "bmp280_main", MYAPP_RTOS_TASK_STACK_SIZE_LARGE, client, RTOS_TASK_PRIORITY_NORMAL, NULL, 1);
    if (xReturned == pdPASS) {
        printf("OK Task bmp280_main has been created, and is running right now\n");
    }

    ESP_LOGI(TAG, "bmp280_main() END");
}
