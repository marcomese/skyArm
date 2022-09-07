/*
 * screen.h
 *
 *  Created on: May 6, 2022
 *      Author: mames
 */

#ifndef SCREEN_H_
#define SCREEN_H_

#include "tiles.h"

typedef struct screen {
    tile_t tiles[TILES_NUM];
    uint8_t currLevel;
    funcPtr_t screenFuncPtr;
} screen_t;

void initScreen(screen_t* scr);
void updateScreen(screen_t* scr, uint8_t zonePressed);

#endif /* SCREEN_H_ */
