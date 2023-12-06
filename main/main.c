#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <components/servo.h>
#include <components/joystick.h>
#include <driver/adc.h>
#include <esp_adc_cal.h>

int horizontalReadingRaw, verticalReadingRaw;  
servo_compare_handle_t servo_handles; 

//Task function to run servos
void read_joystick_input(void *pvParameters)
{
    while(1){
        //getting joystick reading
        horizontalReadingRaw = adc1_get_raw(HORIZONTAL_ADC1);
        verticalReadingRaw = adc1_get_raw(VERTICAL_ADC1); 

        //turning servo arm depending on joystick input
        if(verticalReadingRaw > MIN_WRIST_UP || verticalReadingRaw < MIN_WRIST_DOWN)
        {
            ESP_ERROR_CHECK(mcpwm_comparator_set_compare_value(servo_handles.wristServo, run_servos_to_angle(map_joystick_raw_to_degree(verticalReadingRaw))));
        } 

        if(horizontalReadingRaw > MIN_SHOULDER_RIGHT || horizontalReadingRaw < MIN_SHOULDER_LEFT)
        {
            ESP_ERROR_CHECK(mcpwm_comparator_set_compare_value(servo_handles.shoulderServo, run_servos_to_angle(map_joystick_raw_to_degree(horizontalReadingRaw))));
        }

        vTaskDelay(pdMS_TO_TICKS(100)); 
    }
}

void app_main(void)
{
    //setting up servos
    servo_handles.wristServo = wrist_servo_init(); 
    servo_handles.shoulderServo = shoulder_servo_init(); 

    //creating RTOS task
    xTaskCreate(read_joystick_input, "joystick_task", 4096, &servo_handles, 5, NULL);

    //setting up joystick
    ESP_ERROR_CHECK(joystick_init()); 

    while(1)
    {
        //add delay to not trigger WDT
        vTaskDelay(pdMS_TO_TICKS(50));
    }
    
 
}