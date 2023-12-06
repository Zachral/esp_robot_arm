#ifndef _SERVO_H__
#define _SERVO_H__
#include "driver/mcpwm_prelude.h"

// Please consult the datasheet of your servo before changing the following parameters
#define SERVO_MIN_PULSEWIDTH_US 500  // Minimum pulse width in microsecond
#define SERVO_MAX_PULSEWIDTH_US 2400  // Maximum pulse width in microsecond
#define SERVO_MIN_DEGREE        -90  // Minimum angle
#define SERVO_MAX_DEGREE        90   // Maximum angle

#define WRIST_SERVO_GPIO             14        // GPIO connects to the PWM signal line
#define SHOULDER_SERVO_GIPO          13        // GPIO connects to the PWM signal line
#define SERVO_TIMEBASE_RESOLUTION_HZ 1000000  // 1MHz, 1us per tick
#define SERVO_TIMEBASE_PERIOD        20000    // 20000 ticks, 20ms
#define DEGREE_OF_TURN               55
#define DEGREE_U_TURN                115

typedef struct
{
mcpwm_cmpr_handle_t wristServo;
mcpwm_cmpr_handle_t shoulderServo;
}servo_compare_handle_t;

mcpwm_cmpr_handle_t wrist_servo_init();
mcpwm_cmpr_handle_t shoulder_servo_init(); 
uint32_t run_servos_to_angle(int servoAngle); 

#endif