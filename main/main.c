#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <components/servo.h>

void app_main(void)
{
mcpwm_cmpr_handle_t wristServo = wrist_servo_init(); 

while(1){
    //turning servo arm 90 degrees counter clockwise
    for(int i = 0; i < 95; i++ )
    {
        ESP_ERROR_CHECK(mcpwm_comparator_set_compare_value(wristServo, run_servos_at_speed(i))); 
        printf("%d\n", i);
        vTaskDelay(pdMS_TO_TICKS(50)); 
    }; 
  
        ESP_ERROR_CHECK(mcpwm_comparator_set_compare_value(wristServo, run_servos_at_speed(0))); 
        vTaskDelay(pdMS_TO_TICKS(250)); 

    //turning servo arm 90 degrees clockwise
    for(int i = 0; i > -91; i--)
    {
        ESP_ERROR_CHECK(mcpwm_comparator_set_compare_value(wristServo, run_servos_at_speed(i))); 
        printf("%d\n", i);
        vTaskDelay(pdMS_TO_TICKS(50)); 
    };
}
 
}