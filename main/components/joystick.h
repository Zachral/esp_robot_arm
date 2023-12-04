#ifndef _JOYSTICK_H__
#define _JOYSTICK_H__

#include "esp_adc_cal.h"

#define HORIZONTAL_JOYSTICK_PIN 34
#define VERTICAL_JOYSTICK_PIN   35
#define BUTTON_JOYSTICK_PIN     32
#define HORIZONTAL_ADC1         ADC1_CHANNEL_6
#define VERTICAL_ADC1           ADC1_CHANNEL_7
#define JOYSTICK_BUTTON_ADC1    ADC1_CHANNEL_4
#define MIN_VOLTAGE_UP          2700
#define MIN_VOLTAGE_DOWN        1800
#define MIN_VOLTAGE_LEFT        1600
#define MIN_VOLTAGE_RIGHT       2750

esp_err_t joystick_init(esp_adc_cal_characteristics_t* adc1_charecteristics);
#endif