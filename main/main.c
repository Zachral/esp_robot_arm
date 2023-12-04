#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <components/servo.h>
#include <components/joystick.h>
#include <driver/adc.h>


void app_main(void)
{

//Setting up servos and related variables 
mcpwm_cmpr_handle_t wristServo = wrist_servo_init(); 
mcpwm_cmpr_handle_t shoulderServo = shoulder_servo_init(); 
int horizontal, vertical, shoulderAngle = 0, wristAngle = 0; 
ESP_ERROR_CHECK(mcpwm_comparator_set_compare_value(shoulderServo, run_servos_to_angle(shoulderAngle)));//Setting servos in center position. 
ESP_ERROR_CHECK(mcpwm_comparator_set_compare_value(wristServo, run_servos_to_angle(wristAngle))); 
vTaskDelay(pdMS_TO_TICKS(250)); 

//setting up joystick and related variables
ESP_ERROR_CHECK(joystick_init()); 
uint64_t  horizontalReading, verticalReading;  


while(1){

    horizontalReading = adc1_get_raw(HORIZONTAL_ADC1);
    verticalReading = adc1_get_raw(VERTICAL_ADC1); 
    printf("HORIZONTAL = %lld\nVERTICAL = %lld",horizontalReading,verticalReading); 
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