/*
 * tiles.c
 *
 *  Created on: May 6, 2022
 *      Author: mames
 */

#include "tiles.h"
#include "tilesFunctions.h"

extern uint8_t imgBuf[BAR_SIZE];
extern FIL tileFile;

void drawTile(tile_t tile){
    if(tile.bitmapFile != NULL)
        drawTileFromBMP(tile.id, tile.x, tile.y, tile.w, tile.h, tile.bitmapFile, imgBuf);
    else
        drawTileTxt(tile.x, tile.y, tile.w, tile.h, tile.txt, tile.color, tile.bgcolor);
}

void drawTileChilds(tile_t tile){
    for(int i = 0; i < TILES_NUM; i++){
        tile_t* child = tile.childs[i];

        if(child != NULL)
            drawTile(*child);
    }
}

tile_t T0 =
{
 .id = TILE0,
 .x = TILE0_X,
 .y = TILE0_Y,
 .w = TILE_WIDTH,
 .h = TILE_HEIGHT,
 .color = TILE0_COLOR,
 .bgcolor = TILE0_BGCOLOR,
 .nextLevel = 1,
 .bitmapFile = &tileFile,
 .txt = {"","Measure",""},
 .tileFuncPtr = displayAcqStatus,
 .screenFuncPtr = showMeas,
 .childs = {&thetaT, &phiT, &distT, &pauseT}
};

tile_t thetaT =
{
 .id = TILE0,
 .x = TILE0_X,
 .y = TILE0_Y,
 .w = TILE_WIDTH,
 .h = TILE_HEIGHT,
 .color = TILE0_COLOR,
 .bgcolor = TILE0_BGCOLOR,
 .nextLevel = 1,
 .bitmapFile = NULL,
 .txt = {"Theta","",""},
 .tileFuncPtr = noop,
 .screenFuncPtr = NULL,
 .childs = {NULL, NULL, NULL, NULL}
};

tile_t phiT =
{
 .id = TILE1,
 .x = TILE1_X,
 .y = TILE1_Y,
 .w = TILE_WIDTH,
 .h = TILE_HEIGHT,
 .color = TILE0_COLOR,
 .bgcolor = TILE0_BGCOLOR,
 .nextLevel = 1,
 .bitmapFile = NULL,
 .txt = {"Phi","",""},
 .tileFuncPtr = noop,
 .screenFuncPtr = NULL,
 .childs = {NULL, NULL, NULL, NULL}
};

tile_t distT =
{
 .id = TILE2,
 .x = TILE2_X,
 .y = TILE2_Y,
 .w = TILE_WIDTH,
 .h = TILE_HEIGHT,
 .color = TILE0_COLOR,
 .bgcolor = TILE0_BGCOLOR,
 .nextLevel = 1,
 .bitmapFile = NULL,
 .txt = {"Distance","",""},
 .tileFuncPtr = noop,
 .screenFuncPtr = NULL,
 .childs = {NULL, NULL, NULL, NULL}
};

tile_t pauseT =
{
 .id = TILE3,
 .x = TILE3_X,
 .y = TILE3_Y,
 .w = TILE_WIDTH,
 .h = TILE_HEIGHT,
 .color = TILE0_COLOR,
 .bgcolor = TILE0_BGCOLOR,
 .nextLevel = 1,
 .bitmapFile = NULL,
 .txt = {"Pause","","acquisition"},
 .tileFuncPtr = pauseAcq,
 .screenFuncPtr = NULL,
 .childs = {NULL, NULL, NULL, NULL}
};

tile_t T1 =
{
 .id = TILE1,
 .x = TILE1_X,
 .y = TILE1_Y,
 .w = TILE_WIDTH,
 .h = TILE_HEIGHT,
 .color = TILE1_COLOR,
 .bgcolor = TILE1_BGCOLOR,
 .nextLevel = 1,
 .bitmapFile = &tileFile,
 .txt = {"","Settings",""},
 .tileFuncPtr = noop,
 .screenFuncPtr = NULL,
 .childs = {&calSensT, &saveT, &defaultT, &rotateT}
};

tile_t calSensT =
{
 .id = TILE0,
 .x = TILE0_X,
 .y = TILE0_Y,
 .w = TILE_WIDTH,
 .h = TILE_HEIGHT,
 .color = TILE1_COLOR,
 .bgcolor = TILE1_BGCOLOR,
 .nextLevel = 2,
 .bitmapFile = NULL,
 .txt = {"Sensors","","calibration"},
 .tileFuncPtr = noop,
 .screenFuncPtr = NULL,
 .childs = {&calDistT, &zeroT, &calAngT, &backT}
};

tile_t saveT =
{
 .id = TILE1,
 .x = TILE1_X,
 .y = TILE1_Y,
 .w = TILE_WIDTH,
 .h = TILE_HEIGHT,
 .color = TILE1_COLOR,
 .bgcolor = TILE1_BGCOLOR,
 .nextLevel = 2,
 .bitmapFile = NULL,
 .txt = {"Save","","settings"},
 .tileFuncPtr = saveConfigs,
 .screenFuncPtr = NULL,
 .childs = {NULL, NULL, NULL, NULL}
};

tile_t defaultT =
{
 .id = TILE2,
 .x = TILE2_X,
 .y = TILE2_Y,
 .w = TILE_WIDTH,
 .h = TILE_HEIGHT,
 .color = TILE1_COLOR,
 .bgcolor = TILE1_BGCOLOR,
 .nextLevel = 1,
 .bitmapFile = NULL,
 .txt = {"Reset","","settings"},
 .tileFuncPtr = defaultConfigs,
 .screenFuncPtr = NULL,
 .childs = {NULL, NULL, NULL, NULL}
};

tile_t rotateT =
{
 .id = TILE3,
 .x = TILE3_X,
 .y = TILE3_Y,
 .w = TILE_WIDTH,
 .h = TILE_HEIGHT,
 .color = TILE1_COLOR,
 .bgcolor = TILE1_BGCOLOR,
 .nextLevel = 0,
 .bitmapFile = NULL,
 .txt = {"Rotate","","screen"},
 .tileFuncPtr = rotateScreen,
 .screenFuncPtr = NULL,
 .childs = {NULL, NULL, NULL, NULL}
};

tile_t calDistT =
{
 .id = TILE0,
 .x = TILE0_X,
 .y = TILE0_Y,
 .w = TILE_WIDTH,
 .h = TILE_HEIGHT,
 .color = TILE1_COLOR,
 .bgcolor = TILE1_BGCOLOR,
 .nextLevel = 2,
 .bitmapFile = NULL,
 .txt = {"Distance","","calibration"},
 .tileFuncPtr = calibrateDist,
 .screenFuncPtr = NULL,
 .childs = {NULL, NULL, NULL, NULL}
};

tile_t zeroT =
{
 .id = TILE1,
 .x = TILE1_X,
 .y = TILE1_Y,
 .w = TILE_WIDTH,
 .h = TILE_HEIGHT,
 .color = TILE1_COLOR,
 .bgcolor = TILE1_BGCOLOR,
 .nextLevel = 2,
 .bitmapFile = NULL,
 .txt = {"Set","","zero"},
 .tileFuncPtr = setZero,
 .screenFuncPtr = NULL,
 .childs = {NULL, NULL, NULL, NULL}
};

tile_t calAngT =
{
 .id = TILE2,
 .x = TILE2_X,
 .y = TILE2_Y,
 .w = TILE_WIDTH,
 .h = TILE_HEIGHT,
 .color = TILE1_COLOR,
 .bgcolor = TILE1_BGCOLOR,
 .nextLevel = 2,
 .bitmapFile = NULL,
 .txt = {"Crosstalk","","Calibration"},
 .tileFuncPtr = crossTalkCalib,
 .screenFuncPtr = NULL,
 .childs = {NULL, NULL, NULL, NULL}
};

tile_t backT =
{
 .id = TILE3,
 .x = TILE3_X,
 .y = TILE3_Y,
 .w = TILE_WIDTH,
 .h = TILE_HEIGHT,
 .color = TILE1_COLOR,
 .bgcolor = TILE1_BGCOLOR,
 .nextLevel = 1,
 .bitmapFile = NULL,
 .txt = {"","Back",""},
 .tileFuncPtr = clearInfo,
 .screenFuncPtr = NULL,
 .childs = {&calSensT, &saveT, &defaultT, &rotateT}
};

tile_t T2 =
{
 .id = TILE2,
 .x = TILE2_X,
 .y = TILE2_Y,
 .w = TILE_WIDTH,
 .h = TILE_HEIGHT,
 .color = TILE2_COLOR,
 .bgcolor = TILE2_BGCOLOR,
 .nextLevel = 1,
 .bitmapFile = &tileFile,
 .txt = {"","Log files",""},
 .tileFuncPtr = showLogStatus,
 .screenFuncPtr = NULL,
 .childs = {&enLogT, &disLogT, &dumpLogT, &resetLogT}
};

tile_t enLogT =
{
 .id = TILE0,
 .x = TILE0_X,
 .y = TILE0_Y,
 .w = TILE_WIDTH,
 .h = TILE_HEIGHT,
 .color = TILE2_COLOR,
 .bgcolor = TILE2_BGCOLOR,
 .nextLevel = 1,
 .bitmapFile = NULL,
 .txt = {"Enable","","logging"},
 .tileFuncPtr = enableLog,
 .screenFuncPtr = NULL,
 .childs = {NULL, NULL, NULL, NULL}
};

tile_t disLogT =
{
 .id = TILE1,
 .x = TILE1_X,
 .y = TILE1_Y,
 .w = TILE_WIDTH,
 .h = TILE_HEIGHT,
 .color = TILE2_COLOR,
 .bgcolor = TILE2_BGCOLOR,
 .nextLevel = 1,
 .bitmapFile = NULL,
 .txt = {"Disable","","logging"},
 .tileFuncPtr = disableLog,
 .screenFuncPtr = NULL,
 .childs = {NULL, NULL, NULL, NULL}
};

tile_t dumpLogT =
{
 .id = TILE2,
 .x = TILE2_X,
 .y = TILE2_Y,
 .w = TILE_WIDTH,
 .h = TILE_HEIGHT,
 .color = TILE2_COLOR,
 .bgcolor = TILE2_BGCOLOR,
 .nextLevel = 1,
 .bitmapFile = NULL,
 .txt = {"Dump","","log file"},
 .tileFuncPtr = dumpLog,
 .screenFuncPtr = NULL,
 .childs = {NULL, NULL, NULL, NULL}
};

tile_t resetLogT =
{
 .id = TILE3,
 .x = TILE3_X,
 .y = TILE3_Y,
 .w = TILE_WIDTH,
 .h = TILE_HEIGHT,
 .color = TILE2_COLOR,
 .bgcolor = TILE2_BGCOLOR,
 .nextLevel = 1,
 .bitmapFile = NULL,
 .txt = {"Reset","","log file"},
 .tileFuncPtr = resetLogFile,
 .screenFuncPtr = NULL,
 .childs = {NULL, NULL, NULL, NULL}
};

tile_t T3 =
{
 .id = TILE3,
 .x = TILE3_X,
 .y = TILE3_Y,
 .w = TILE_WIDTH,
 .h = TILE_HEIGHT,
 .color = TILE3_COLOR,
 .bgcolor = TILE3_BGCOLOR,
 .nextLevel = 1,
 .bitmapFile = &tileFile,
 .txt = {"","Monitor",""},
 .tileFuncPtr = displayMonStatus,
 .screenFuncPtr = NULL,
 .childs = {&enMonT, &disMonT, &monNull1T, &monNull2T}
};

tile_t enMonT =
{
 .id = TILE0,
 .x = TILE0_X,
 .y = TILE0_Y,
 .w = TILE_WIDTH,
 .h = TILE_HEIGHT,
 .color = TILE3_COLOR,
 .bgcolor = TILE3_BGCOLOR,
 .nextLevel = 1,
 .bitmapFile = NULL,
 .txt = {"Enable","","monitor"},
 .tileFuncPtr = enableMon,
 .screenFuncPtr = NULL,
 .childs = {NULL, NULL, NULL, NULL}
};

tile_t disMonT =
{
 .id = TILE1,
 .x = TILE1_X,
 .y = TILE1_Y,
 .w = TILE_WIDTH,
 .h = TILE_HEIGHT,
 .color = TILE3_COLOR,
 .bgcolor = TILE3_BGCOLOR,
 .nextLevel = 1,
 .bitmapFile = NULL,
 .txt = {"Disable","","monitor"},
 .tileFuncPtr = disableMon,
 .screenFuncPtr = NULL,
 .childs = {NULL, NULL, NULL, NULL}
};

tile_t monNull1T =
{
 .id = TILE2,
 .x = TILE2_X,
 .y = TILE2_Y,
 .w = TILE_WIDTH,
 .h = TILE_HEIGHT,
 .color = TILE3_COLOR,
 .bgcolor = TILE3_BGCOLOR,
 .nextLevel = 1,
 .bitmapFile = NULL,
 .txt = {"","",""},
 .tileFuncPtr = noop,
 .screenFuncPtr = NULL,
 .childs = {NULL, NULL, NULL, NULL}
};

tile_t monNull2T =
{
 .id = TILE3,
 .x = TILE3_X,
 .y = TILE3_Y,
 .w = TILE_WIDTH,
 .h = TILE_HEIGHT,
 .color = TILE3_COLOR,
 .bgcolor = TILE3_BGCOLOR,
 .nextLevel = 1,
 .bitmapFile = NULL,
 .txt = {"","",""},
 .tileFuncPtr = noop,
 .screenFuncPtr = NULL,
 .childs = {NULL, NULL, NULL, NULL}
};
