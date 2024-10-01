#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/adc.h"

TaskHandle_t adcReadTaskHandle;

void adcReadTask(void *arg)
{
    int adc_value;

    while (1)
    {
        adc_value = adc1_get_raw(ADC1_CHANNEL_3);
        printf("ADC Value : %d\n", adc_value);

        vTaskDelay(pdMS_TO_TICKS(2000));
    }
}
void app_main(void)
{
    adc1_config_channel_atten(ADC1_CHANNEL_3, ADC_ATTEN_DB_11);
    adc1_config_width(ADC_WIDTH_BIT_12);

    xTaskCreate(adcReadTask, "adcReadTask", 4096, NULL, 5, adcReadTaskHandle);
}
