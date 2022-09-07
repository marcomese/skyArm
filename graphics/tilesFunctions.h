/*
 * tilesFunctions.h
 *
 *  Created on: 5 mag 2022
 *      Author: mames
 */

#ifndef TILESFUNCTIONS_H_
#define TILESFUNCTIONS_H_

#include <string.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdint.h>

#define TIME_BEFORE_DISTCAL 10

void noop();
void rotateScreen();
void debugInfo();
void showMeas();
void displayAcqStatus();
void pauseAcq();
void calibrateDist();
void crossTalkCalib();
void calibrateAng();
void saveConfigs();
void defaultConfigs();
void setZero();
void enableLog();
void disableLog();
void dumpLog();
void resetLogFile();
void showLogStatus();
void displayMonStatus();
void enableMon();
void disableMon();
extern void clearInfo();

#endif /* TILESFUNCTIONS_H_ */
