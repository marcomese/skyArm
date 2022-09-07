/*
 * screen.c
 *
 *  Created on: May 6, 2022
 *      Author: mames
 */

#include "screen.h"
#include "tilesFunctions.h"

extern uint8_t sdMounted;

void initScreen(screen_t* scr){
    if(!sdMounted){
        T0.bitmapFile = NULL;
        T1.bitmapFile = NULL;
        T2.bitmapFile = NULL;
        T3.bitmapFile = NULL;
    }

    scr->currLevel = 0;
    scr->screenFuncPtr = noop;
    scr->tiles[0] = T0;
    scr->tiles[1] = T1;
    scr->tiles[2] = T2;
    scr->tiles[3] = T3;

    for(int i = 0; i < TILES_NUM; i++)
        drawTile(scr->tiles[i]);

    clearInfo();
}

void updateScreen(screen_t* scr, uint8_t zonePressed){
    tile_t* childPtr;
    tile_t temp[TILES_NUM];
    tile_t pressedTile = scr->tiles[zonePressed];
    funcPtr_t tileFunc = pressedTile.tileFuncPtr;
    funcPtr_t scrFunc = pressedTile.screenFuncPtr;

    scr->currLevel = pressedTile.nextLevel;
    if(scrFunc != NULL)
        scr->screenFuncPtr = scrFunc;

    if(zonePressed != HOME){
        for(int i = 0; i < TILES_NUM; i++){
            childPtr = pressedTile.childs[i];

            if(childPtr != NULL){
                drawTile(*childPtr);
                temp[i] = *childPtr;
            }else
                temp[i] = scr->tiles[i];
        }

        for(int i = 0; i < TILES_NUM; i++)
            scr->tiles[i] = temp[i];

        tileFunc();
    }else
        initScreen(scr);
}
