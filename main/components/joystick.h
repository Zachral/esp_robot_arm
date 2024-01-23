#ifndef _JOYSTICK_H__
#define _JOYSTICK_H__

#include "esp_adc_cal.h"

#define HORIZONTAL_JOYSTICK_PIN 34
#define VERTICAL_JOYSTICK_PIN   35
#define BUTTON_JOYSTICK_PIN     32
#define HORIZONTAL_ADC1         ADC1_CHANNEL_6
#define VERTICAL_ADC1           ADC1_CHANNEL_7
#define JOYSTICK_BUTTON_ADC1    ADC1_CHANNEL_4
#define MIN_WRIST_UP            2100
#define MIN_WRIST_DOWN          1600
#define MIN_SHOULDER_LEFT       2600
#define MIN_SHOULDER_RIGHT      2900
#define MIN_RAW_INPUT           0
#define MAX_RAW_INPUT           4095
#define MIN_DEGREE              -90
#define MAX_DEGREE              90

esp_err_t joystick_init();
int map_joystick_raw_to_degree(int input); 

#endif