/*
 * timerDelay.h
 *
 *  Created on: Dec 31, 2021
 *      Author: mames
 */

#ifndef INC_TIMERDELAY_H_
#define INC_TIMERDELAY_H_

#include "stm32l4xx_hal.h"

void delay_us(uint32_t us);
void delay_ms(uint32_t ms);
void inv_icm20948_sleep_us(int us);
uint64_t inv_icm20948_get_time_us(void);

#endif /* INC_TIMERDELAY_H_ */
