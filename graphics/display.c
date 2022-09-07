/*
 * display.c
 *
 *  Created on: 3 mag 2022
 *      Author: mames
 */

#include "display.h"

void loadBMP(FIL* bmpFile, uint8_t* imgBuf, uint32_t bufSize, uint8_t imgOffset){
    uint8_t temp;
    unsigned int bytesRead = 0;
    uint32_t dataOffset = imgOffset*bufSize;

    memset(imgBuf, 0, bufSize);

    f_lseek(bmpFile, BMP_DATA_OFFSET+dataOffset);
    f_read(bmpFile, imgBuf, bufSize, &bytesRead);

    for(int i = 0; i < bufSize/2; i++){
        temp = imgBuf[bufSize-i-1];
        imgBuf[bufSize-i-1] = imgBuf[i];
        imgBuf[i] = temp;
    }
}

void drawTileFromBMP(uint8_t tileID, uint16_t x, uint16_t y, uint16_t w, uint16_t h, FIL* fil, uint8_t* imgBuf){
    unsigned int imgOffset;

    switch(tileID){
    case TILE0:
        imgOffset = 0;
        break;
    case TILE1:
        imgOffset = 1;
        break;
    case TILE2:
        imgOffset = 2;
        break;
    case TILE3:
        imgOffset = 3;
        break;
    case HOME:
        imgOffset = 4;
        break;
    default:
        imgOffset = 0;
        break;
    }

    loadBMP(fil, imgBuf, 2*w*h, imgOffset);
    ILI9341_DrawImage(x, y, w, h, (const uint16_t*)imgBuf);
}

void drawTileTxt(uint16_t x, uint16_t y, uint16_t w, uint16_t h, const char** txtRow, uint16_t color, uint16_t bgcolor){
    char buffer[TILE_STRLEN];

    ILI9341_FillRectangle(x, y, w, h, bgcolor);
    for(int i = 0; i < TILE_ROWS; i++)
        if(strncmp(txtRow[i],"",TILE_STRLEN) != 0){
            snprintf(buffer,TILE_STRLEN,txtRow[i]);
            ILI9341_WriteString(x+10, y+10+i*18, buffer, Font_11x18, color, bgcolor);
        }
}

void drawBar(FIL* fil, uint8_t* imgBuf){
    ILI9341_FillScreen(BGCOLOR);

    loadBMP(fil, imgBuf, BAR_SIZE, 0);

    ILI9341_DrawImage(BAR_X, BAR_Y, BAR_WIDTH, BAR_HEIGHT, (const uint16_t*)imgBuf);
}

void transformCoord(uint16_t touchX, uint16_t touchY,
                    uint16_t* dispX, uint16_t* dispY,
                    uint8_t orientation, bool valid){
    if(valid){
        switch(orientation){
        case ILI9341_ROTATION_R:
            *dispX = touchY;
            *dispY = touchX;
            break;
        case ILI9341_ROTATION_L:
            *dispX = ILI9341_WIDTH-touchY;
            *dispY = ILI9341_HEIGHT-touchX;
            break;
        }
    }
}

uint8_t getZonePressed(uint16_t x, uint16_t y){
    uint8_t zone = 0;

    if(x <= ZONE0_X && y <= ZONE0_Y){
        zone = TILE0;
    }else if(x > ZONE1_X && y <= ZONE1_Y){
        zone = TILE1;
    }else if(x <= ZONE2_X && y > ZONE2_Y && y <= ZONE_HOME_Y){
        zone = TILE2;
    }else if(x > ZONE3_X && y > ZONE3_Y && y <= ZONE_HOME_Y){
        zone = TILE3;
    }else if(x > ZONE_HOME_X && y > ZONE_HOME_Y){
        zone = HOME;
    }

    return zone;
}

void displayInfo(uint8_t infoID, FontDef font, const char* infoStr, ...){
    static char buffer[INFO_STRLEN_7x10];
    va_list args;
    uint16_t infoBGcolor = 0;
    char* cleanStr = "             ";
    uint8_t fontStrLen;

    switch(font.width){
    case 7:
        fontStrLen = INFO_STRLEN_7x10;
        break;
    case 11:
        fontStrLen = INFO_STRLEN_11x18;
        break;
    case 16:
        fontStrLen = INFO_STRLEN_16x26;
        break;
    default:
        fontStrLen = INFO_STRLEN_16x26;
        break;
    }

    va_start(args, infoStr);
    vsnprintf(buffer, fontStrLen, infoStr, args);
    va_end(args);

    switch(infoID){
    case INFO_LOG:
        infoBGcolor = ILI9341_GREEN;
        break;
    case INFO_ERROR:
        infoBGcolor = ILI9341_RED;
        break;
    case INFO_WARN:
        infoBGcolor = ILI9341_YELLOW;
        break;
    default:
        infoBGcolor = ILI9341_GREEN;
        break;
    }

    ILI9341_FillRectangle(INFO_STR_X, INFO_STR_Y, INFO_STR_W, INFO_STR_H, infoBGcolor);
    ILI9341_WriteString(INFO_X, INFO_Y, cleanStr, font, BGCOLOR, infoBGcolor);
    ILI9341_WriteString(INFO_X, INFO_Y, buffer, font, ILI9341_BLACK, infoBGcolor);
}

void clearInfo(){
    ILI9341_FillRectangle(INFO_STR_X, INFO_STR_Y, INFO_STR_W, INFO_STR_H, BGCOLOR);
}
