/*
 * configurations.h
 *
 *  Created on: Mar 9, 2022
 *      Author: mames
 */

#ifndef INC_CONFIGURATIONS_H_
#define INC_CONFIGURATIONS_H_

#define VL53L1X_MAX_DISTANCE 2000 // max distance in mm
#define EXPECTED_WHOAMI      0xEA
#define HW_UNITS             1073741824L

#define THETA_IDX 0
#define PHI_IDX   1

#define BTN_NONE      0U
#define BTN_UP        1U
#define BTN_OK        2U
#define BTN_DOWN      3U
#define JOY_UP        4U
#define JOY_PRESS     5U
#define JOY_DOWN      6U
#define JOY_LEFT      7U
#define JOY_RIGHT     8U

#define HOME_SCR      0
#define CONFIG_SCR    1
#define INFO_SCR      2
#define DCALIB_SCR    3
#define ACALIB_SCR    4
#define SAVE_SCR      5

#define CFG_OFF_POS   15
#define CFG_DCAL_POS  20
#define CFG_ACAL_POS  (CFG_DCAL_POS + CFG_OFF_POS)
#define CFG_SAVE_POS  (CFG_ACAL_POS + CFG_OFF_POS)

#endif /* INC_CONFIGURATIONS_H_ */
