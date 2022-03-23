/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32l4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "configurations.h"
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define LCD_RST_Pin GPIO_PIN_0
#define LCD_RST_GPIO_Port GPIOA
#define VCP_TX_Pin GPIO_PIN_2
#define VCP_TX_GPIO_Port GPIOA
#define DAC_LEN_Pin GPIO_PIN_4
#define DAC_LEN_GPIO_Port GPIOA
#define DAC_ANG_Pin GPIO_PIN_5
#define DAC_ANG_GPIO_Port GPIOA
#define BTN_DOWN_Pin GPIO_PIN_0
#define BTN_DOWN_GPIO_Port GPIOB
#define BTN_DOWN_EXTI_IRQn EXTI0_IRQn
#define BTN_OK_Pin GPIO_PIN_1
#define BTN_OK_GPIO_Port GPIOB
#define BTN_OK_EXTI_IRQn EXTI1_IRQn
#define MUX_SEL_Pin GPIO_PIN_8
#define MUX_SEL_GPIO_Port GPIOA
#define BTN_UP_Pin GPIO_PIN_11
#define BTN_UP_GPIO_Port GPIOA
#define BTN_UP_EXTI_IRQn EXTI15_10_IRQn
#define JOY_RIGHT_Pin GPIO_PIN_12
#define JOY_RIGHT_GPIO_Port GPIOA
#define JOY_RIGHT_EXTI_IRQn EXTI15_10_IRQn
#define SWDIO_Pin GPIO_PIN_13
#define SWDIO_GPIO_Port GPIOA
#define SWCLK_Pin GPIO_PIN_14
#define SWCLK_GPIO_Port GPIOA
#define VCP_RX_Pin GPIO_PIN_15
#define VCP_RX_GPIO_Port GPIOA
#define JOY_PRESS_Pin GPIO_PIN_3
#define JOY_PRESS_GPIO_Port GPIOB
#define JOY_PRESS_EXTI_IRQn EXTI3_IRQn
#define JOY_UP_Pin GPIO_PIN_5
#define JOY_UP_GPIO_Port GPIOB
#define JOY_UP_EXTI_IRQn EXTI9_5_IRQn
#define JOY_DOWN_Pin GPIO_PIN_6
#define JOY_DOWN_GPIO_Port GPIOB
#define JOY_DOWN_EXTI_IRQn EXTI9_5_IRQn
#define JOY_LEFT_Pin GPIO_PIN_7
#define JOY_LEFT_GPIO_Port GPIOB
#define JOY_LEFT_EXTI_IRQn EXTI9_5_IRQn
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
