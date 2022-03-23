/*
 * interface.h
 *
 *  Created on: Mar 20, 2022
 *      Author: mames
 */

#ifndef INC_INTERFACE_H_
#define INC_INTERFACE_H_

typedef void (*funcPtr_t)(void*);

typedef struct screen{
        const unsigned char* bitmap;
        funcPtr_t auxFuncPtr;
        funcPtr_t inputParsePtr;
} screen_t;

#endif /* INC_INTERFACE_H_ */
