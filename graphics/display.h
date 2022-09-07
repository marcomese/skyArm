/*
 * display.h
 *
 *  Created on: 3 mag 2022
 *      Author: mames
 */

#ifndef DISPLAY_H_
#define DISPLAY_H_

#include "ili9341.h"
#include "fonts.h"
#include "ili9341_touch.h"
#include "fatfs.h"
#include <string.h>
#include <stdarg.h>
#include <stdio.h>

#define DISP_ORIENTATION ILI9341_ROTATION_R

#define BMP_DATA_OFFSET 138

#define TILE_WIDTH  154
#define TILE_HEIGHT 74
#define TILE_SPACE  4

#define BAR_WIDTH  (2*TILE_WIDTH+TILE_SPACE)
#define BAR_HEIGHT TILE_HEIGHT

#define COLOR_BYTES 2
#define TILE_SIZE   COLOR_BYTES*TILE_WIDTH*TILE_HEIGHT
#define BAR_SIZE    COLOR_BYTES*BAR_WIDTH*BAR_HEIGHT
#define BAR_X 4
#define BAR_Y 160

#define INFO_STRLEN_16x26 14
#define INFO_STRLEN_11x18 20
#define INFO_STRLEN_7x10  28
#define INFO_X 24
#define INFO_Y 184
#define INFO_STR_X INFO_X-7
#define INFO_STR_Y INFO_Y-11
#define INFO_STR_W 224
#define INFO_STR_H 48
#define INFO_LOG    0
#define INFO_ERROR  1
#define INFO_WARN   2

#define TILE_ROWS 3
#define TILES_NUM 4
#define TILE_STRLEN 14
#define TILE0_X 4
#define TILE0_Y 4
#define TILE1_X 162
#define TILE1_Y 4
#define TILE2_X 4
#define TILE2_Y 82
#define TILE3_X 162
#define TILE3_Y 82
#define HOME_X  250
#define HOME_Y  160
#define TILE0 0
#define TILE1 1
#define TILE2 2
#define TILE3 3
#define HOME  4

#define MAX_LEVELS 3
#define ZONE_NUM 5

#define ZONE0_X 150
#define ZONE0_Y 80
#define ZONE1_X 160
#define ZONE1_Y 80
#define ZONE2_X 160
#define ZONE2_Y 80
#define ZONE3_X 160
#define ZONE3_Y 80
#define ZONE_HOME_X 250
#define ZONE_HOME_Y 160

#define BGCOLOR       ILI9341_COLOR565(61,  105, 117)
#define TILE0_COLOR   ILI9341_COLOR565(214, 251, 206)
#define TILE0_BGCOLOR ILI9341_COLOR565(41,  154, 33)
#define TILE1_COLOR   ILI9341_COLOR565(165, 210, 247)
#define TILE1_BGCOLOR ILI9341_COLOR565(0,   154, 255)
#define TILE2_COLOR   ILI9341_COLOR565(239, 198, 197)
#define TILE2_BGCOLOR ILI9341_COLOR565(214, 45,  41)
#define TILE3_COLOR   ILI9341_COLOR565(230, 202, 156)
#define TILE3_BGCOLOR ILI9341_COLOR565(214, 150, 41)

void loadBMP(FIL* bmpFile, uint8_t* imgBuf, uint32_t bufSize, uint8_t imgOffset);
void drawTileTxt(uint16_t x, uint16_t y, uint16_t w, uint16_t h, const char** txtRow, uint16_t color, uint16_t bgcolor);
void drawTileFromBMP(uint8_t tileID, uint16_t x, uint16_t y, uint16_t w, uint16_t h, FIL* fil, uint8_t* imgBuf);
void drawBar(FIL* fil, uint8_t* imgBuf);
uint8_t getZonePressed(uint16_t x, uint16_t y);
void transformCoord(uint16_t touchX, uint16_t touchY, uint16_t* dispX, uint16_t* dispY, uint8_t orientation, bool valid);
void displayInfo(uint8_t infoID, FontDef font, const char* infoStr, ...);

#endif /* DISPLAY_H_ */
