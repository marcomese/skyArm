/*
 * timerDelay.c
 *
 *  Created on: Dec 31, 2021
 *      Author: mames
 */

#include "timerDelay.h"

extern TIM_HandleTypeDef htim6;

static void start_timer(void)
{
    HAL_TIM_Base_Start(&htim6);
}

static void stop_timer(void)
{
    HAL_TIM_Base_Stop(&htim6);
}

static void internal_delay(uint16_t us)
{
    const uint16_t start = __HAL_TIM_GET_COUNTER(&htim6);

    uint32_t now, prev = 0;
    do{
        now = __HAL_TIM_GET_COUNTER(&htim6);

        /* handle rollover */
        if(now < prev)
            now = UINT16_MAX + now;
        prev = now;

    }while((now - start) <= us);
}

void delay_us(uint32_t us)
{
    uint32_t i;

    start_timer();

    /* in case the delay is up to UINT16_MAX */
    if(us >= UINT16_MAX) {
        /* go to the loop as the internal_delay function only support uint16_t argument type */
        for(i = 0; i < (us / UINT16_MAX); i++)
            internal_delay(UINT16_MAX);
        internal_delay(us % UINT16_MAX);
    }
    else
        internal_delay(us);

    stop_timer();
}

void delay_ms(uint32_t ms)
{
    delay_us(ms*1000);
}

void inv_icm20948_sleep_us(int us){
    delay_us(us);
}

uint64_t inv_icm20948_get_time_us(void){
    return (uint64_t)(__HAL_TIM_GET_COUNTER(&htim6));
}
