/*
 * tiles.h
 *
 *  Created on: May 6, 2022
 *      Author: mames
 */

#ifndef TILES_H_
#define TILES_H_

#include "display.h"

typedef void (*funcPtr_t)(void);

typedef struct tile {
    uint8_t       id;
    uint16_t      x;
    uint16_t      y;
    uint16_t      w;
    uint16_t      h;
    uint16_t      color;
    uint16_t      bgcolor;
    uint8_t       nextLevel;
    FIL*          bitmapFile;
    const char*   txt[TILE_ROWS];
    struct tile*  childs[TILES_NUM];
    funcPtr_t     tileFuncPtr;
    funcPtr_t     screenFuncPtr;
} tile_t;

void drawTile(tile_t tile);
void drawTileChilds(tile_t tile);

extern tile_t T0;
extern tile_t thetaT;
extern tile_t phiT;
extern tile_t distT;
extern tile_t pauseT;

extern tile_t T1;
extern tile_t calSensT;
extern tile_t calDistT;
extern tile_t calAngT;
extern tile_t backT;
extern tile_t saveT;
extern tile_t defaultT;
extern tile_t rotateT;
extern tile_t zeroT;

extern tile_t T2;
extern tile_t enLogT;
extern tile_t disLogT;
extern tile_t dumpLogT;
extern tile_t resetLogT;

extern tile_t T3;
extern tile_t enMonT;
extern tile_t disMonT;
extern tile_t monNull1T;
extern tile_t monNull2T;

#endif /* TILES_H_ */
