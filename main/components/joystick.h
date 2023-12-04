#ifndef _JOYSTICK_H__
#define _JOYSTICK_H__

#include "driver/adc.h"

#define HORIZONTAL_JOYSTICK_PIN 34
#define VERTICAL_JOYSTICK_PIN   35
#define BUTTON_JOYSTICK_PIN     32
#define HORIZONTAL_ADC1         ADC1_CHANNEL_6
#define VERTICAL_ADC1           ADC1_CHANNEL_7
#define JOYSTICK_BUTTON_ADC1    ADC1_CHANNEL_4

esp_err_t joystick_init(); 
#endif