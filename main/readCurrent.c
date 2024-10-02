#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/adc.h"
#include "esp_adc_cal.h"

#define MAX_VOLTAGE 3300 // mv
#define SAMPLE_PER_PERIOD 100
#define PERIOD_MS 20
#define SAMPLE_INTERVAL_MS (PERIOD_MS / SAMPLE_PER_PERIOD)

#define SENSITIVITY 66 // 66 mV/A for ACS712-30A
#define ACS_OFFSET 2366 // mv
TaskHandle_t adcReadTaskHandle;

esp_adc_cal_characteristics_t adc_chars;

void adcReadTask(void *arg)
{
    int adc_value;
    uint32_t sample_voltage;
    uint32_t cal_voltage;
    uint32_t sum_voltage;
    uint32_t voltage;
    float current;
    while (1)
    {
        sum_voltage = 0;
        for (int i = 0; i < SAMPLE_PER_PERIOD; i++)
        {
            //  Method 1: Read raw ADC value
            adc_value = adc1_get_raw(ADC1_CHANNEL_3);
            sample_voltage = (adc_value / 4095.0) * MAX_VOLTAGE;
            
            // Method 2: Get calibrated voltage for more accuracy
            esp_adc_cal_get_voltage(ADC1_CHANNEL_3, &adc_chars, &cal_voltage);
           
            // Average voltage from both methods
            sum_voltage += (sample_voltage + cal_voltage) / 2;

            vTaskDelay(pdMS_TO_TICKS(SAMPLE_INTERVAL_MS));
        }

        voltage = sum_voltage / SAMPLE_PER_PERIOD;

        printf(" Voltage: %d ", voltage);

        current = (voltage - ACS_OFFSET) / SENSITIVITY ;
        printf(" Current: %.3f \n", current);

        vTaskDelay(pdMS_TO_TICKS(2000));
    }
}
void app_main(void)
{
    adc1_config_channel_atten(ADC1_CHANNEL_3, ADC_ATTEN_DB_11);
    adc1_config_width(ADC_WIDTH_BIT_12);

    esp_adc_cal_characterize(ADC_UNIT_1, ADC_ATTEN_DB_11, ADC_WIDTH_BIT_12, ESP_ADC_CAL_VAL_EFUSE_VREF, &adc_chars);

    xTaskCreate(adcReadTask, "adcReadTask", 4096, NULL, 5, adcReadTaskHandle);
}
