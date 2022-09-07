/*
 * I2CSerifHal.h
 *
 *  Created on: Dec 30, 2021
 *      Author: mames
 */

#ifndef INC_I2CSERIFHAL_H_
#define INC_I2CSERIFHAL_H_

#include "stm32l4xx_hal.h"
#include "Invn/Devices/SerifHal.h"

#define I2C_SLAVE_ADDRESS 0x69
#define MAX_RW_TRANS_SIZE 255U

const inv_serif_hal_t* get_serif_inst_i2c(void);

#endif /* INC_I2CSERIFHAL_H_ */
