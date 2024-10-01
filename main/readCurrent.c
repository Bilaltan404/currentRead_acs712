#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/adc.h"
#include "esp_adc_cal.h"

#define MAX_VOLTAGE 3292 // mv

TaskHandle_t adcReadTaskHandle;

 esp_adc_cal_characteristics_t adc_chars;

void adcReadTask(void *arg)
{
    int adc_value;
    double voltage;
    uint32_t cal_voltage;

    while (1)
    {
        // Method 1
        adc_value = adc1_get_raw(ADC1_CHANNEL_3);
        printf("ADC Value : %d ", adc_value);

        voltage = ((double)adc_value / 4095.0) * MAX_VOLTAGE;
        printf("Voltage : %.3f ",voltage);

        // Method 2
        esp_adc_cal_get_voltage(ADC1_CHANNEL_3,&adc_chars,&cal_voltage); // Method 2 have more accuracy than method 1
        printf("Calibrated Voltage: %d \n",cal_voltage);

        vTaskDelay(pdMS_TO_TICKS(2000));
    }
}
void app_main(void)
{
    adc1_config_channel_atten(ADC1_CHANNEL_3, ADC_ATTEN_DB_11);
    adc1_config_width(ADC_WIDTH_BIT_12);

    esp_adc_cal_characterize(ADC_UNIT_1, ADC_ATTEN_DB_11, ADC_WIDTH_BIT_12,ESP_ADC_CAL_VAL_EFUSE_VREF, &adc_chars);

    xTaskCreate(adcReadTask, "adcReadTask", 4096, NULL, 5, adcReadTaskHandle);
}
