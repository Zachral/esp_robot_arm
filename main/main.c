#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <components/servo.h>

void app_main(void)
{
mcpwm_cmpr_handle_t wristServo = wrist_servo_init(); 
mcpwm_cmpr_handle_t shoulderServo = shoulder_servo_init(); 

while(1){
    //Setting servos in center position.
    ESP_ERROR_CHECK(mcpwm_comparator_set_compare_value(shoulderServo, run_servos_to_angle(0))); 
    ESP_ERROR_CHECK(mcpwm_comparator_set_compare_value(wristServo, run_servos_to_angle(0))); 
    vTaskDelay(pdMS_TO_TICKS(250)); 

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