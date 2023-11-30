#include "joystick.h"
#include "driver/gpio.h"

void joystick_init()
{
    ESP_ERROR_CHECK(gpio_set_direction(HORIZONTAL_JOYSTICK_PIN, GPIO_MODE_INPUT));
    ESP_ERROR_CHECK(gpio_set_direction(VERTICAL_JOYSTICK_PIN, GPIO_MODE_INPUT));
    ESP_ERROR_CHECK(gpio_reset_pin(BUTTON_JOYSTICK_PIN));
    ESP_ERROR_CHECK(gpio_set_pull_mode(BUTTON_JOYSTICK_PIN, GPIO_PULLUP_ONLY)); 
    ESP_ERROR_CHECK(gpio_set_direction(BUTTON_JOYSTICK_PIN, GPIO_MODE_INPUT));
return; 
}