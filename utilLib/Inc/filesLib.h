/*
 * filesLib.h
 *
 *  Created on: 27 mag 2022
 *      Author: mames
 */

#ifndef INC_FILESLIB_H_
#define INC_FILESLIB_H_

#include "fatfs.h"
#include "string.h"
#include "display.h"

#define CFGSTR_LEN 20
#define LOGSTR_LEN 180
#define UARTSTR_LEN 170
#define TIMESTR_LEN 12

FRESULT readConfig(uint32_t* cfgArray);
FRESULT writeConfig(uint32_t* cfgArray);
int readLog(char* logStr);
unsigned int writeLog(const char* logStr);
unsigned int resetLog(void);

#endif /* INC_FILESLIB_H_ */
