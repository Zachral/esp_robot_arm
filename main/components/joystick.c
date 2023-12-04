#include "joystick.h"
#include "driver/gpio.h"
#include "driver/adc.h"
#include "esp_adc_cal.h"

esp_err_t joystick_init(esp_adc_cal_characteristics_t* adc1_charecteristics)
{
    //Setting up the voltage range to 11db (~150-2450mV).
    adc1_config_channel_atten(HORIZONTAL_ADC1, ADC_ATTEN_DB_11); //Horizontal pin
    adc1_config_channel_atten(VERTICAL_ADC1, ADC_ATTEN_DB_11); //Vertical pin
    adc1_config_channel_atten(JOYSTICK_BUTTON_ADC1, ADC_ATTEN_DB_11); //Button pin

    //Calibrate the voltage on ADC1 on 11dB
    esp_adc_cal_characterize(ADC_UNIT_1, ADC_ATTEN_DB_11, ADC_WIDTH_BIT_DEFAULT, 0, adc1_charecteristics); 

    //Configure BIT width, DEFAULT is 12-bits.
    adc1_config_width(ADC_WIDTH_BIT_DEFAULT);

    //Set GIPO direction on pins. 
    ESP_ERROR_CHECK(gpio_set_direction(HORIZONTAL_JOYSTICK_PIN, GPIO_MODE_INPUT));
    ESP_ERROR_CHECK(gpio_set_direction(VERTICAL_JOYSTICK_PIN, GPIO_MODE_INPUT));
    ESP_ERROR_CHECK(gpio_reset_pin(BUTTON_JOYSTICK_PIN));
    ESP_ERROR_CHECK(gpio_set_pull_mode(BUTTON_JOYSTICK_PIN, GPIO_PULLUP_ONLY)); 
    ESP_ERROR_CHECK(gpio_set_direction(BUTTON_JOYSTICK_PIN, GPIO_MODE_INPUT));

return ESP_OK; 
}