/*
 * SPDX-FileCopyrightText: 2022-2023 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include <stdint.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "driver/mcpwm_prelude.h"
#include "servo.h"

static const char *L = "Left servo";
static const char *R = "Right servo"; 
 
// int servoSpeed = 80;

uint32_t run_servos_to_angle(int servoAngle){
    return (servoAngle - SERVO_MIN_DEGREE) * (SERVO_MAX_PULSEWIDTH_US - SERVO_MIN_PULSEWIDTH_US) / (SERVO_MAX_DEGREE - SERVO_MIN_DEGREE) + SERVO_MIN_PULSEWIDTH_US;
};


mcpwm_cmpr_handle_t wrist_servo_init(){
    /*Initilizes wrist servo*/
    ESP_LOGI(L, "Create timer and operator");
    mcpwm_timer_handle_t wrist_servo_timer = NULL;
    mcpwm_timer_config_t wrist_servo_timer_config = {
        .group_id = 0,
        .clk_src = MCPWM_TIMER_CLK_SRC_DEFAULT,
        .resolution_hz = SERVO_TIMEBASE_RESOLUTION_HZ,
        .period_ticks = SERVO_TIMEBASE_PERIOD,
        .count_mode = MCPWM_TIMER_COUNT_MODE_UP,
    };
    ESP_ERROR_CHECK(mcpwm_new_timer(&wrist_servo_timer_config, &wrist_servo_timer));

    mcpwm_oper_handle_t wrist_servo_operator = NULL;
    mcpwm_operator_config_t wrist_servo_operator_config = {
        .group_id = 0, // operator must be in the same group to the timer
    };
    ESP_ERROR_CHECK(mcpwm_new_operator(&wrist_servo_operator_config, &wrist_servo_operator));

    ESP_LOGI(L, "Connect timer and operator");
    ESP_ERROR_CHECK(mcpwm_operator_connect_timer(wrist_servo_operator, wrist_servo_timer));

    ESP_LOGI(L, "Create comparator and generator from the operator");
    mcpwm_cmpr_handle_t wrist_servo_comparator = NULL;
    mcpwm_comparator_config_t wrist_servo_comparator_config = {
        .flags.update_cmp_on_tez = true,
    };
    ESP_ERROR_CHECK(mcpwm_new_comparator(wrist_servo_operator, &wrist_servo_comparator_config, &wrist_servo_comparator));

    mcpwm_gen_handle_t wrist_servo_generator = NULL;
    mcpwm_generator_config_t wrist_servo_generator_config = {
        .gen_gpio_num = WRIST_SERVO_GPIO,
    };
    ESP_ERROR_CHECK(mcpwm_new_generator(wrist_servo_operator, &wrist_servo_generator_config, &wrist_servo_generator));

    // set the initial compare value, so that the servo will spin to the center position
    ESP_ERROR_CHECK(mcpwm_comparator_set_compare_value(wrist_servo_comparator, run_servos_to_angle(0)));

    ESP_LOGI(L, "Set generator action on timer and compare event");
    // go high on counter empty
    ESP_ERROR_CHECK(mcpwm_generator_set_action_on_timer_event(wrist_servo_generator,
                                                              MCPWM_GEN_TIMER_EVENT_ACTION(MCPWM_TIMER_DIRECTION_UP, MCPWM_TIMER_EVENT_EMPTY, MCPWM_GEN_ACTION_HIGH)));
    // go low on compare threshold
    ESP_ERROR_CHECK(mcpwm_generator_set_action_on_compare_event(wrist_servo_generator,
                                                                MCPWM_GEN_COMPARE_EVENT_ACTION(MCPWM_TIMER_DIRECTION_UP, wrist_servo_comparator, MCPWM_GEN_ACTION_LOW)));

    ESP_LOGI(L, "Enable and start timer");
    ESP_ERROR_CHECK(mcpwm_timer_enable(wrist_servo_timer));
    ESP_ERROR_CHECK(mcpwm_timer_start_stop(wrist_servo_timer, MCPWM_TIMER_START_NO_STOP));

    return wrist_servo_comparator;
}

mcpwm_cmpr_handle_t shoulder_servo_init(){
    /*Initilizes shoulder servo*/
    ESP_LOGI(R, "Create timer and operator");
    mcpwm_timer_handle_t shoulder_servo_timer = NULL;
    mcpwm_timer_config_t shoulder_servo_timer_config = {
        .group_id = 1,
        .clk_src = MCPWM_TIMER_CLK_SRC_DEFAULT,
        .resolution_hz = SERVO_TIMEBASE_RESOLUTION_HZ,
        .period_ticks = SERVO_TIMEBASE_PERIOD,
        .count_mode = MCPWM_TIMER_COUNT_MODE_UP,
    };
    ESP_ERROR_CHECK(mcpwm_new_timer(&shoulder_servo_timer_config, &shoulder_servo_timer));

    mcpwm_oper_handle_t shoulder_servo_operator = NULL;
    mcpwm_operator_config_t shoulder_servo_operator_config = {
        .group_id = 1, // operator must be in the same group to the timer
    };
    ESP_ERROR_CHECK(mcpwm_new_operator(&shoulder_servo_operator_config, &shoulder_servo_operator));

    ESP_LOGI(R, "Connect timer and operator");
    ESP_ERROR_CHECK(mcpwm_operator_connect_timer(shoulder_servo_operator, shoulder_servo_timer));

    ESP_LOGI(R, "Create comparator and generator from the operator");
    mcpwm_cmpr_handle_t shoulder_servo_comparator = NULL;
    mcpwm_comparator_config_t shoulder_servo_comparator_config = {
        .flags.update_cmp_on_tez = true,
    };
    ESP_ERROR_CHECK(mcpwm_new_comparator(shoulder_servo_operator, &shoulder_servo_comparator_config, &shoulder_servo_comparator));

    mcpwm_gen_handle_t shoulder_servo_generator = NULL;
    mcpwm_generator_config_t shoulder_servo_generator_config = {
        .gen_gpio_num = SHOULDER_SERVO_GIPO,
    };
    ESP_ERROR_CHECK(mcpwm_new_generator(shoulder_servo_operator, &shoulder_servo_generator_config, &shoulder_servo_generator));

    //set the initial compare value, so that the servo will spin to the center position
    ESP_ERROR_CHECK(mcpwm_comparator_set_compare_value(shoulder_servo_comparator, run_servos_to_angle(0)));

    ESP_LOGI(R, "Set generator action on timer and compare event");
    // go high on counter empty
    ESP_ERROR_CHECK(mcpwm_generator_set_action_on_timer_event(shoulder_servo_generator,
                                                              MCPWM_GEN_TIMER_EVENT_ACTION(MCPWM_TIMER_DIRECTION_UP, MCPWM_TIMER_EVENT_EMPTY, MCPWM_GEN_ACTION_HIGH)));
    // go low on compare threshold
    ESP_ERROR_CHECK(mcpwm_generator_set_action_on_compare_event(shoulder_servo_generator,
                                                                MCPWM_GEN_COMPARE_EVENT_ACTION(MCPWM_TIMER_DIRECTION_UP, shoulder_servo_comparator, MCPWM_GEN_ACTION_LOW)));

    ESP_LOGI(R, "Enable and start timer");
    ESP_ERROR_CHECK(mcpwm_timer_enable(shoulder_servo_timer));
    ESP_ERROR_CHECK(mcpwm_timer_start_stop(shoulder_servo_timer, MCPWM_TIMER_START_NO_STOP));
    return shoulder_servo_comparator;
    }

