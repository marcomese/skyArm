/*
 * filesLib.c
 *
 *  Created on: 27 mag 2022
 *      Author: mames
 */

#include "filesLib.h"

FRESULT readConfig(uint32_t* cfgArray){
    FIL fil;
    uint32_t cfgData = 0;
    unsigned int bytesRead;

    FRESULT fres = f_open(&fil, "cfg.dat", FA_READ | FA_OPEN_EXISTING);
    if(fres != FR_OK)
        return fres;

    for(int i = 0; i < CFG_WORDS; i++){
        fres = f_read(&fil, &cfgData, sizeof(uint32_t), &bytesRead);
        if(fres != FR_OK)
            return fres;

        memcpy((void*)cfgArray++, (void*)&cfgData, sizeof(uint32_t));
    }

    f_close(&fil);

    return FR_OK;
}

FRESULT writeConfig(uint32_t* cfgArray){
    FIL fil;
    unsigned int bytesWrote;

    FRESULT fres = f_open(&fil, "cfg.dat", FA_WRITE | FA_OPEN_ALWAYS);
    if(fres != FR_OK)
        return fres;

    for(int i = 0; i < CFG_WORDS; i++){
        fres = f_write(&fil, cfgArray++, sizeof(uint32_t), &bytesWrote);
        if(fres != FR_OK)
            return fres;
    }

    f_close(&fil);

    return FR_OK;
}

unsigned int resetLog(void){
    FIL fil;
    unsigned int bytesWrote;

    FRESULT fres = f_open(&fil, "log.dat", FA_WRITE | FA_CREATE_ALWAYS);
    if(fres != FR_OK){
        displayInfo(INFO_ERROR, Font_11x18, "Cannot open log.dat!");
        return fres;
    }

    bytesWrote = f_puts("=== LOG FILE ===\n", &fil);
    f_close(&fil);

    if(bytesWrote < 0){
        displayInfo(INFO_ERROR, Font_11x18, "Cannot write on log.dat!");
        return fres;
    }

    return FR_OK;
}

int readLog(char* logStr){
    FIL fil;
    char readBuf[LOGSTR_LEN] = "";
    unsigned int bytesRead = 0;
    static unsigned int totalBytes = 0;

    FRESULT fres = f_open(&fil, "log.dat", FA_READ | FA_OPEN_EXISTING);
    if(fres != FR_OK){
        displayInfo(INFO_ERROR, Font_11x18, "Cannot open log.dat!");
        return fres;
    }

    f_lseek(&fil, totalBytes);
    f_gets(readBuf, LOGSTR_LEN, &fil);
    f_close(&fil);

    bytesRead = strlen(readBuf);

    if(bytesRead){
        memcpy(logStr, readBuf, bytesRead);
        totalBytes += bytesRead+1;
        return FR_OK;
    }else{
        totalBytes = 0;
        return EOF;
    }
}


unsigned int writeLog(const char* logStr){
    FIL fil;
    char readBuf[LOGSTR_LEN];
    unsigned int bytesWrote;

    FRESULT fres = f_open(&fil, "log.dat", FA_WRITE | FA_OPEN_APPEND);
    if(fres != FR_OK){
        displayInfo(INFO_ERROR, Font_11x18, "Cannot open log.dat!");
        return fres;
    }

    strncpy((char*)readBuf, logStr, LOGSTR_LEN);

    bytesWrote = f_puts(logStr, &fil);
    f_close(&fil);

    if(bytesWrote < 0){
        displayInfo(INFO_ERROR, Font_11x18, "Cannot write on log.dat!");
        return fres;
    }

    return bytesWrote;
}
