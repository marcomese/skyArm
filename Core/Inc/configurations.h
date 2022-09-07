/*
 * configurations.h
 *
 *  Created on: Mar 9, 2022
 *      Author: mames
 */

#ifndef INC_CONFIGURATIONS_H_
#define INC_CONFIGURATIONS_H_

#define VL53L1X_MAX_DISTANCE 2500 // max distance in mm
#define EXPECTED_WHOAMI      0xEA
#define HW_UNITS             1073741824L

#define THETA_IDX 0
#define PHI_IDX   1

#define CFG_WORDS 5
#define DISTCAL_IDX 0
#define THETAZERO_IDX 1
#define PHIZERO_IDX 2
#define SORIENT_IDX 3
#define DISTXTALK_IDX 4

#define DIST_MODE_THRESHOLD 600
#define VL53L1X_LONG_DIST_MODE 2
#define VL53L1X_SHORT_DIST_MODE 1

#define VREFINT 2
#define VREFINTCAL_ADDR 0x1FFF75AA

#define DAC_MAX 3700

#endif /* INC_CONFIGURATIONS_H_ */
