#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <components/servo.h>
#include <components/joystick.h>
#include <driver/adc.h>
#include <esp_adc_cal.h>

void app_main(void)
{

//Setting up servos and related variables 
mcpwm_cmpr_handle_t wristServo = wrist_servo_init(); 
mcpwm_cmpr_handle_t shoulderServo = shoulder_servo_init(); 
int shoulderAngle = 0, wristAngle = 0; 
ESP_ERROR_CHECK(mcpwm_comparator_set_compare_value(shoulderServo, run_servos_to_angle(shoulderAngle)));//Setting servos in center position. 
ESP_ERROR_CHECK(mcpwm_comparator_set_compare_value(wristServo, run_servos_to_angle(wristAngle))); 
vTaskDelay(pdMS_TO_TICKS(250)); 

//setting up joystick and related variables
static esp_adc_cal_characteristics_t adc1_charecteristics; 
ESP_ERROR_CHECK(joystick_init(&adc1_charecteristics)); 
int horizontalReadingRaw, verticalReadingRaw, horizontalVoltage, verticalVoltage;   


while(1){

    horizontalReadingRaw = adc1_get_raw(HORIZONTAL_ADC1);
    verticalReadingRaw = adc1_get_raw(VERTICAL_ADC1); 
    horizontalVoltage =esp_adc_cal_raw_to_voltage(horizontalReadingRaw, &adc1_charecteristics); 
    verticalVoltage =esp_adc_cal_raw_to_voltage(verticalReadingRaw, &adc1_charecteristics); 
    printf("HORIZONTAL = %d VERTICAL = %d\n",horizontalVoltage,verticalVoltage); 
    vTaskDelay(pdMS_TO_TICKS(250)); 

    // //turning servo arm 45 degrees counter clockwise
    // ESP_ERROR_CHECK(mcpwm_comparator_set_compare_value(wristServo, run_servos_to_angle(45)));
    // ESP_ERROR_CHECK(mcpwm_comparator_set_compare_value(shoulderServo, run_servos_to_angle(-45))); 
    // vTaskDelay(pdMS_TO_TICKS(250)); 

    // //Setting servos in center position.
    // ESP_ERROR_CHECK(mcpwm_comparator_set_compare_value(wristServo, run_servos_to_angle(0))); 
    // ESP_ERROR_CHECK(mcpwm_comparator_set_compare_value(shoulderServo, run_servos_to_angle(0)));
    // vTaskDelay(pdMS_TO_TICKS(250)); 

    // //turning servo arm 45 degrees clockwise
    // ESP_ERROR_CHECK(mcpwm_comparator_set_compare_value(wristServo, run_servos_to_angle(45))); 
    // ESP_ERROR_CHECK(mcpwm_comparator_set_compare_value(shoulderServo, run_servos_to_angle(45)));
    // vTaskDelay(pdMS_TO_TICKS(250)); 
    
}
 
}