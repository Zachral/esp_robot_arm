#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <components/servo.h>

void app_main(void)
{
mcpwm_cmpr_handle_t wristServo = wrist_servo_init(); 
mcpwm_cmpr_handle_t shoulderServo = shoulder_servo_init(); 
int horizontal;
int vertical;
int shoulderAngle = 0;
int wristAngle = 0; 

//Setting servos in center position.
ESP_ERROR_CHECK(mcpwm_comparator_set_compare_value(shoulderServo, run_servos_to_angle(shoulderAngle))); 
ESP_ERROR_CHECK(mcpwm_comparator_set_compare_value(wristServo, run_servos_to_angle(wristAngle))); 
vTaskDelay(pdMS_TO_TICKS(250)); 

while(1){

   horizontal =


    //turning servo arm 45 degrees counter clockwise
    ESP_ERROR_CHECK(mcpwm_comparator_set_compare_value(wristServo, run_servos_to_angle(45)));
    ESP_ERROR_CHECK(mcpwm_comparator_set_compare_value(shoulderServo, run_servos_to_angle(-45))); 
    vTaskDelay(pdMS_TO_TICKS(250)); 

    //Setting servos in center position.
    ESP_ERROR_CHECK(mcpwm_comparator_set_compare_value(wristServo, run_servos_to_angle(0))); 
    ESP_ERROR_CHECK(mcpwm_comparator_set_compare_value(shoulderServo, run_servos_to_angle(0)));
    vTaskDelay(pdMS_TO_TICKS(250)); 

    //turning servo arm 45 degrees clockwise
    ESP_ERROR_CHECK(mcpwm_comparator_set_compare_value(wristServo, run_servos_to_angle(45))); 
    ESP_ERROR_CHECK(mcpwm_comparator_set_compare_value(shoulderServo, run_servos_to_angle(45)));
    vTaskDelay(pdMS_TO_TICKS(250)); 
    
}
 
}