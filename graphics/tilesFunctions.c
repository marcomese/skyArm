/*
 * tilesFunctions.c
 *
 *  Created on: 5 mag 2022
 *      Author: mames
 */

#include "Invn/Devices/DeviceIcm20948.h"
#include "tilesFunctions.h"
#include "configurations.h"
#include "screen.h"
#include "display.h"
#include "vl53l1x_api.h"
#include "vl53l1x_calibration.h"
#include "filesLib.h"
#include "tiles.h"

#define THETA_STR_X TILE0_X+10
#define THETA_STR_Y TILE0_Y+54
#define DIST_STR_X  TILE1_X+10
#define DIST_STR_Y  TILE1_Y+54
#define PHI_STR_X   TILE2_X+10
#define PHI_STR_Y   TILE2_Y+54

extern inv_device_icm20948_t imu;
extern uint8_t screenOrient;
extern screen_t menu;
extern FIL barFile;
extern uint8_t imgBuf[BAR_SIZE];
extern uint16_t vl53l1xDev;
extern int16_t distOffset;
extern int16_t distXtalk;
extern volatile float angToLCD[2];
extern volatile float distToDisp;
extern volatile uint8_t acqPaused;
extern volatile uint8_t logEnabled;
extern volatile uint8_t dumpLogEnabled;
extern volatile uint8_t monitorEnabled;
extern volatile float phi, theta;
extern volatile float phiZero, thetaZero;
extern uint32_t config[CFG_WORDS];
extern uint32_t defConfig[CFG_WORDS];
extern volatile uint16_t distMode;
volatile float lastAng[2];
volatile float lastDist;

extern void check_rc(int rc);

void noop() {}

void rotateScreen(){
    screenOrient = (screenOrient == ILI9341_ROTATION_R) ?
            ILI9341_ROTATION_L : ILI9341_ROTATION_R;

    ILI9341_SetOrientation(screenOrient);

    drawBar(&barFile, imgBuf);

    initScreen(&menu);

    memcpy((void*)&config[SORIENT_IDX], (void*)&screenOrient, sizeof(uint32_t));

    return;
}

void displayAcqStatus(){
    switch(acqPaused){
    case 1:
        displayInfo(INFO_WARN, Font_16x26, "Acq. paused");
        break;
    case 0:
        displayInfo(INFO_LOG, Font_16x26, "Running");
        break;
    }

    return;
}

void pauseAcq(){
    if(acqPaused){
        acqPaused = 0;
        pauseT.txt[0] = "Pause";
    }else{
        acqPaused = 1;
        pauseT.txt[0] = "Resume";
        lastDist = distToDisp;
        lastAng[THETA_IDX] = angToLCD[THETA_IDX];
        lastAng[PHI_IDX] = angToLCD[PHI_IDX];
    }

    drawTile(pauseT);

    displayAcqStatus();

    return;
}

void dispMeasInTiles(float dist, float theta, float phi){
    char buffer[TILE_STRLEN];

    snprintf(buffer, TILE_STRLEN, "%.1f",theta);
    ILI9341_FillRectangle(THETA_STR_X, THETA_STR_Y-5, 9*16, 26, TILE0_BGCOLOR);
    ILI9341_WriteString(THETA_STR_X, THETA_STR_Y-5, buffer, Font_16x26, TILE0_COLOR, TILE0_BGCOLOR);

    snprintf(buffer, TILE_STRLEN, "%.1f",phi);
    ILI9341_FillRectangle(DIST_STR_X, DIST_STR_Y-5, 9*16, 26, TILE0_BGCOLOR);
    ILI9341_WriteString(DIST_STR_X, DIST_STR_Y-5, buffer, Font_16x26, TILE0_COLOR, TILE0_BGCOLOR);

    snprintf(buffer, TILE_STRLEN, "%.4fm",dist);
    ILI9341_FillRectangle(PHI_STR_X, PHI_STR_Y-5, 9*16, 26, TILE0_BGCOLOR);
    ILI9341_WriteString(PHI_STR_X, PHI_STR_Y-5, buffer, Font_16x26, TILE0_COLOR, TILE0_BGCOLOR);

    return;
}

void showMeas(){
    if(!acqPaused){
        dispMeasInTiles(distToDisp, angToLCD[THETA_IDX], angToLCD[PHI_IDX]);
    }else{
        dispMeasInTiles(lastDist, lastAng[THETA_IDX], lastAng[PHI_IDX]);
    }

    return;
}

void calibrateDist(){
    VL53L1X_StopRanging(vl53l1xDev);

    VL53L1X_SetDistanceMode(vl53l1xDev, VL53L1X_SHORT_DIST_MODE);

    for(int i = TIME_BEFORE_DISTCAL; i > 0; i--){
        displayInfo(INFO_LOG, Font_11x18, "Starting in %ds", i);
        HAL_Delay(1000);
    }

    displayInfo(INFO_WARN, Font_11x18, "Calibrating...");

    while(VL53L1X_CalibrateOffset(vl53l1xDev, 140, &distOffset)){}

    memcpy((void*)&config[DISTCAL_IDX], (void*)&distOffset, sizeof(uint32_t));

    VL53L1X_SetOffset(vl53l1xDev,distOffset);

    VL53L1X_SetDistanceMode(vl53l1xDev, distMode);

    VL53L1X_StartRanging(vl53l1xDev);

    displayInfo(INFO_LOG, Font_11x18, "Calibration done!");

    return;
}

void crossTalkCalib(){
    VL53L1X_StopRanging(vl53l1xDev);

    VL53L1X_SetDistanceMode(vl53l1xDev, VL53L1X_LONG_DIST_MODE);

    for(int i = TIME_BEFORE_DISTCAL; i > 0; i--){
        displayInfo(INFO_LOG, Font_11x18, "Starting in %ds", i);
        HAL_Delay(1000);
    }

    displayInfo(INFO_WARN, Font_11x18, "Calibrating...");

    while(VL53L1X_CalibrateXtalk(vl53l1xDev, 1500, &distXtalk)){}

    memcpy((void*)&config[DISTXTALK_IDX], (void*)&distXtalk, sizeof(uint32_t));

    VL53L1X_SetXtalk(vl53l1xDev,distXtalk);

    VL53L1X_SetDistanceMode(vl53l1xDev, distMode);

    VL53L1X_StartRanging(vl53l1xDev);

    displayInfo(INFO_LOG, Font_11x18, "Calibration done!");

    return;
}

void saveConfigs(){
    FRESULT fres;

    fres = writeConfig(config);
    if(fres != FR_OK){
        displayInfo(INFO_ERROR, Font_11x18, "Cannot save config.");
        return;
    }

    displayInfo(INFO_LOG, Font_11x18, "Config. saved!");

    return;
}

void defaultConfigs(){
    FRESULT fres;

    fres =  writeConfig(defConfig);
    if(fres != FR_OK){
        displayInfo(INFO_ERROR, Font_11x18, "Cannot save config.");
        return;
    }

    VL53L1X_StopRanging(vl53l1xDev);
    VL53L1X_SetOffset(vl53l1xDev,defConfig[DISTCAL_IDX]);
    VL53L1X_StartRanging(vl53l1xDev);

    memcpy((void*)&thetaZero, (void*)&defConfig[THETAZERO_IDX], sizeof(float));
    memcpy((void*)&phiZero, (void*)&defConfig[PHIZERO_IDX], sizeof(float));

    ILI9341_SetOrientation(defConfig[SORIENT_IDX]);

    screenOrient = defConfig[SORIENT_IDX];

    drawBar(&barFile, imgBuf);

    initScreen(&menu);

    displayInfo(INFO_LOG, Font_11x18, "Reset to default!");

    return;
}

void setZero(){
    acqPaused = 1;

    thetaZero = theta;
    phiZero = phi;

    memcpy((void*)&config[THETAZERO_IDX], (void*)&thetaZero, sizeof(uint32_t));
    memcpy((void*)&config[PHIZERO_IDX], (void*)&phiZero, sizeof(uint32_t));

    displayInfo(INFO_LOG, Font_11x18, "Current position 0");
    acqPaused = 0;

    return;
}

void showLogStatus(){
    switch(logEnabled){
    case 1:
        displayInfo(INFO_LOG, Font_11x18, "Log enabled!");
        break;
    case 0:
        displayInfo(INFO_LOG, Font_11x18, "Log disabled!");
        break;
    }

    return;
}

void enableLog(){
    logEnabled = 1;

    displayInfo(INFO_LOG, Font_11x18, "Log enabled!");

    return;
}

void disableLog(){
    logEnabled = 0;

    displayInfo(INFO_LOG, Font_11x18, "Log disabled!");

    return;
}

void resetLogFile(){
    resetLog();

    displayInfo(INFO_LOG, Font_11x18, "Logs cleared!");
}

void dumpLog(){
    char dumpStr[LOGSTR_LEN] = "";
    logEnabled = 0;
    acqPaused = 1;

    displayInfo(INFO_WARN, Font_11x18, "Dumping logs on uart...");

    while(readLog(dumpStr) != EOF){
        printf("%s",dumpStr);
    }

    printf("=== END LOG ===\n");
    displayInfo(INFO_LOG, Font_11x18, "Log file dumped!");

    acqPaused = 0;

    return;
}

void displayMonStatus(){
    switch(monitorEnabled){
    case 1:
        displayInfo(INFO_LOG, Font_11x18, "Monitor enabled!");
        break;
    case 0:
        displayInfo(INFO_WARN, Font_11x18, "Monitor disabled!");
        break;
    }

    return;
}

void enableMon(){
    monitorEnabled = 1;

    displayInfo(INFO_LOG, Font_11x18, "Monitor enabled!");

    return;
}

void disableMon(){
    monitorEnabled = 0;

    displayInfo(INFO_WARN, Font_11x18, "Monitor disabled!");

    return;
}

//static void apply_stored_offsets(void)
//{
//    uint8_t sensor_bias[84];
//    int32_t acc_bias_q16[6] = {0}, gyro_bias_q16[6] = {0};
//    uint8_t i, idx = 0;
//    int rc;
//
//    for(i = 0; i < 6; i++)
//        gyro_bias_q16[i] = inv_dc_little8_to_int32((const uint8_t *)(&sensor_bias[i * sizeof(uint32_t)]));
//
//    idx += sizeof(gyro_bias_q16);
//
//    rc = inv_device_set_sensor_config(device, INV_SENSOR_TYPE_GYROSCOPE,
//        VSENSOR_CONFIG_TYPE_OFFSET, gyro_bias_q16, sizeof(gyro_bias_q16));
//    check_rc(rc);
//
//    for(i = 0; i < 6; i++)
//        acc_bias_q16[i] = inv_dc_little8_to_int32((const uint8_t *)(&sensor_bias[idx + i * sizeof(uint32_t)]));
//
//    idx += sizeof(acc_bias_q16);
//
//    rc = inv_device_set_sensor_config(device, INV_SENSOR_TYPE_ACCELEROMETER,
//        VSENSOR_CONFIG_TYPE_OFFSET, acc_bias_q16, sizeof(acc_bias_q16));
//}

void calibrateAng(){
//    int selfTestRes = 0;
//    int rc = 0;
//    inv_device_t* device;
//
//    device = inv_device_icm20948_get_base(&imu);

    displayInfo(INFO_WARN, Font_11x18, "Not implemented yet...");

//    rc = inv_device_stop_sensor(device, INV_SENSOR_TYPE_ACCELEROMETER);
//    check_rc(rc);
//    rc = inv_device_stop_sensor(device, INV_SENSOR_TYPE_GYROSCOPE);
//    check_rc(rc);
//    rc = inv_device_stop_sensor(device, INV_SENSOR_TYPE_MAGNETOMETER);
//    check_rc(rc);
//    rc = inv_device_stop_sensor(device, INV_SENSOR_TYPE_ROTATION_VECTOR);
//    check_rc(rc);
//
//    if(imu.icm20948_states.selftest_done != 1){
//        selfTestRes = inv_icm20948_run_selftest(&(imu.icm20948_states));
//
//        if(selfTestRes == 7){
//            printf("Self Test OK\r\n");
//            printf("GYRO: %d %d %d\r\n",
//                   imu.icm20948_states.gyro_st_data[0],
//                   imu.icm20948_states.gyro_st_data[1],
//                   imu.icm20948_states.gyro_st_data[2]);
//            printf("ACCEL: %d %d %d\r\n",
//                   imu.icm20948_states.accel_st_data[0],
//                   imu.icm20948_states.accel_st_data[1],
//                   imu.icm20948_states.accel_st_data[2]);
//
//            imu.icm20948_states.selftest_done = 1;
//
//            displayInfo(INFO_LOG, Font_11x18, "Calibration done!");
//
//            inv_device_icm20948_set_sensor_config(&imu,
//                                                  INV_SENSOR_TYPE_ACCELEROMETER,
//                                                  INV_DEVICE_ICM20948_CONFIG_OFFSET,
//                                                  imu.icm20948_states.accel_st_data,
//                                                  0);
//            inv_device_icm20948_set_sensor_config(&imu,
//                                                  INV_SENSOR_TYPE_GYROSCOPE,
//                                                  INV_DEVICE_ICM20948_CONFIG_OFFSET,
//                                                  imu.icm20948_states.gyro_st_data,
//                                                  0);
//        }else{
//            displayInfo(INFO_ERROR, Font_11x18, "Calibration failed!");
//        }
//    }
//
//    rc = inv_device_start_sensor(device, INV_SENSOR_TYPE_ACCELEROMETER);
//    check_rc(rc);
//    rc = inv_device_start_sensor(device, INV_SENSOR_TYPE_GYROSCOPE);
//    check_rc(rc);
//    rc = inv_device_start_sensor(device, INV_SENSOR_TYPE_MAGNETOMETER);
//    check_rc(rc);
//    rc = inv_device_start_sensor(device, INV_SENSOR_TYPE_ROTATION_VECTOR);
//    check_rc(rc);
}
