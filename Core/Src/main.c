/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "Invn/Devices/DeviceIcm20948.h"
#include "Invn/EmbUtils/Message.h"
#include "I2CSerifHal.h"
#include "timerDelay.h"
#include <math.h>
#include <stdio.h>
#include "retarget.h"
#include "sh1106.h"
#include "sh1106_fonts.h"
#include "custom_fonts.h"
#include "vl53l1x_api.h"
#include "vl53l1x_calibration.h"
#include "bitmaps.h"
#include "interface.h"
#include "vl53l1_error_codes.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
ADC_HandleTypeDef hadc1;
DMA_HandleTypeDef hdma_adc1;

DAC_HandleTypeDef hdac1;

I2C_HandleTypeDef hi2c1;
I2C_HandleTypeDef hi2c3;

TIM_HandleTypeDef htim2;
TIM_HandleTypeDef htim6;
TIM_HandleTypeDef htim7;

UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_ADC1_Init(void);
static void MX_I2C1_Init(void);
static void MX_I2C3_Init(void);
static void MX_DMA_Init(void);
static void MX_TIM6_Init(void);
static void MX_DAC1_Init(void);
static void MX_TIM7_Init(void);
static void MX_TIM2_Init(void);
/* USER CODE BEGIN PFP */
static VL53L1X_ERROR initVL53L1X(void);
static inv_device_t* initICM20948(void);
static void msgPrinter(int level, const char * str, va_list ap);
static void sensor_event_cb(const inv_sensor_event_t * event, void * arg);
static void check_rc(int rc);
static uint8_t selectScreen(uint8_t btn, uint8_t currScreen);
static void homeAuxFunc();
static void configAuxFunc();
static void infoAuxFunc();
static void joyParseFunc();
static void noop();
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
static inv_device_icm20948_t imu;

static uint16_t vl53l1xDev=0x52;
//static uint16_t vl53l1xDev=0x53;

static const inv_sensor_listener_t sensor_listener = {
                                                      sensor_event_cb, /* callback that will receive sensor events */
                                                      0                /* some pointer passed to the callback */
};

static const uint8_t dmp3_image[] = {
#include "Invn/Images/icm20948_img.dmp3a.h"
};

//static const uint8_t gyroBias[] = {172, 186, 199};
//static const uint8_t accelBias[] = {112, 106, 129};

volatile float m[3] = {0.0, 0.0, 0.0};
volatile float a[3] = {0.0, 0.0, 0.0};
volatile float g[3] = {0.0, 0.0, 0.0};
volatile float o[3] = {0.0, 0.0, 0.0};
volatile float phi = 0.0, theta = 0.0, psi = 0.0;
volatile uint8_t acc = 0;
uint16_t dist = 0;
volatile uint32_t distToDAC = 0;
volatile uint32_t angToDAC[2] = { 0, 0 };
volatile float angToLCD[2] = { 0.0, 0.0 };

volatile uint8_t dacIndex = 0;

typedef struct btnDesc{
    uint8_t buttonEvent;
    GPIO_TypeDef* gpioPort;
    uint16_t gpioPin;
} btnDesc_t;

volatile btnDesc_t buttonDesc = {
                                 .buttonEvent = BTN_NONE,
                                 .gpioPort = NULL,
                                 .gpioPin = BTN_NONE
};
volatile uint8_t buttonPressed = BTN_NONE;

const screen_t screens[] = {
                            {homeScreen, homeAuxFunc, noop},
                            {configScreen, configAuxFunc, joyParseFunc},
                            {infoScreen, infoAuxFunc, noop},
};

typedef struct cfgScreenArg{
    uint8_t btnPressed;
    uint8_t currScreen;
    uint8_t cursorPos;
} cfgScreenArg_t;

cfgScreenArg_t cfgArg = {
                         .btnPressed = BTN_NONE,
                         .currScreen = 0,
                         .cursorPos = CFG_DCAL_POS
};
/* USER CODE END 0 */

/**
 * @brief  The application entry point.
 * @retval int
 */
int main(void)
{
    /* USER CODE BEGIN 1 */
    int rc = 0;
    int distStatus = 0;
    uint8_t dataReady = 0;
    inv_device_t* device;

    uint8_t screenIdx = 0;
    /* USER CODE END 1 */

    /* MCU Configuration--------------------------------------------------------*/

    /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
    HAL_Init();

    /* USER CODE BEGIN Init */

    /* USER CODE END Init */

    /* Configure the system clock */
    SystemClock_Config();

    /* USER CODE BEGIN SysInit */

    /* USER CODE END SysInit */

    /* Initialize all configured peripherals */
    MX_GPIO_Init();
    MX_USART2_UART_Init();
    MX_ADC1_Init();
    MX_I2C1_Init();
    MX_I2C3_Init();
    MX_DMA_Init();
    MX_TIM6_Init();
    MX_DAC1_Init();
    MX_TIM7_Init();
    MX_TIM2_Init();
    /* USER CODE BEGIN 2 */
    RetargetInit(&huart2);

    sh1106_Init();

    printf("PICOBARN\nLoading...\n");

    sh1106_WriteString("PICOBARN", Font_16x26, White);
    sh1106_SetCursor(5,30);
    sh1106_WriteString("Loading...", Font_7x10, White);
    sh1106_SetCursor(2,0);
    sh1106_UpdateScreen();

    INV_MSG_SETUP(INV_MSG_LEVEL_MAX,msgPrinter);

    distStatus = initVL53L1X();

    if(distStatus != -1)
        VL53L1X_StartRanging(vl53l1xDev);

    device = initICM20948();

    HAL_TIM_Base_Start(&htim6);
    HAL_TIM_Base_Start_IT(&htim2);

    HAL_DAC_Start(&hdac1, DAC1_CHANNEL_1);
    HAL_DAC_Start(&hdac1, DAC1_CHANNEL_2);

    sh1106_Fill(Black);
    sh1106_DrawBitmap(0, 0, homeScreen, 128, 64, White);
    sh1106_UpdateScreen();

    printf("All started, ready to go\n");

    /* USER CODE END 2 */

    /* Infinite loop */
    /* USER CODE BEGIN WHILE */
    while (1)
    {
        /* USER CODE END WHILE */

        /* USER CODE BEGIN 3 */

        if(buttonPressed != BTN_NONE){
            screenIdx = selectScreen(buttonPressed,screenIdx);

            sh1106_Fill(Black);
            sh1106_DrawBitmap(0, 0, screens[screenIdx].bitmap, 128, 64, White);

            cfgArg.btnPressed = buttonPressed;
            screens[screenIdx].inputParsePtr((void*)&cfgArg);

            buttonPressed = BTN_NONE;
        }

        screens[screenIdx].auxFuncPtr((void*)&cfgArg);

        if(distStatus != -1){ // aggiungere decimo di millimetro
            VL53L1X_CheckForDataReady(vl53l1xDev, &dataReady);
            if(dataReady == 1){
                dataReady = 0;
                VL53L1X_GetDistance(vl53l1xDev, &dist);
                distToDAC = (dist >= VL53L1X_MAX_DISTANCE) ?
                        4095 : (dist*4095)/VL53L1X_MAX_DISTANCE;
            }
        }

        rc = inv_device_poll(device);
        check_rc(rc);

        printf("\r$phi=%3.2f,theta=%3.2f,psi=%3.2f,dist=%d",phi,theta,psi,dist);

    }
    /* USER CODE END 3 */
}

/**
 * @brief System Clock Configuration
 * @retval None
 */
void SystemClock_Config(void)
{
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

    /** Configure the main internal regulator output voltage
     */
    if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1) != HAL_OK)
    {
        Error_Handler();
    }

    /** Initializes the RCC Oscillators according to the specified parameters
     * in the RCC_OscInitTypeDef structure.
     */
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
    RCC_OscInitStruct.HSIState = RCC_HSI_ON;
    RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
    RCC_OscInitStruct.PLL.PLLM = 1;
    RCC_OscInitStruct.PLL.PLLN = 10;
    RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV7;
    RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
    RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
    {
        Error_Handler();
    }

    /** Initializes the CPU, AHB and APB buses clocks
     */
    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
            |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
    {
        Error_Handler();
    }
}

/**
 * @brief ADC1 Initialization Function
 * @param None
 * @retval None
 */
static void MX_ADC1_Init(void)
{

    /* USER CODE BEGIN ADC1_Init 0 */

    /* USER CODE END ADC1_Init 0 */

    ADC_ChannelConfTypeDef sConfig = {0};

    /* USER CODE BEGIN ADC1_Init 1 */

    /* USER CODE END ADC1_Init 1 */

    /** Common config
     */
    hadc1.Instance = ADC1;
    hadc1.Init.ClockPrescaler = ADC_CLOCK_ASYNC_DIV4;
    hadc1.Init.Resolution = ADC_RESOLUTION_12B;
    hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
    hadc1.Init.ScanConvMode = ADC_SCAN_ENABLE;
    hadc1.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
    hadc1.Init.LowPowerAutoWait = DISABLE;
    hadc1.Init.ContinuousConvMode = ENABLE;
    hadc1.Init.NbrOfConversion = 3;
    hadc1.Init.DiscontinuousConvMode = DISABLE;
    hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
    hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
    hadc1.Init.DMAContinuousRequests = ENABLE;
    hadc1.Init.Overrun = ADC_OVR_DATA_OVERWRITTEN;
    hadc1.Init.OversamplingMode = DISABLE;
    if (HAL_ADC_Init(&hadc1) != HAL_OK)
    {
        Error_Handler();
    }

    /** Configure Regular Channel
     */
    sConfig.Channel = ADC_CHANNEL_6;
    sConfig.Rank = ADC_REGULAR_RANK_1;
    sConfig.SamplingTime = ADC_SAMPLETIME_640CYCLES_5;
    sConfig.SingleDiff = ADC_SINGLE_ENDED;
    sConfig.OffsetNumber = ADC_OFFSET_NONE;
    sConfig.Offset = 0;
    if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
    {
        Error_Handler();
    }

    /** Configure Regular Channel
     */
    sConfig.Channel = ADC_CHANNEL_8;
    sConfig.Rank = ADC_REGULAR_RANK_2;
    if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
    {
        Error_Handler();
    }

    /** Configure Regular Channel
     */
    sConfig.Channel = ADC_CHANNEL_11;
    sConfig.Rank = ADC_REGULAR_RANK_3;
    if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
    {
        Error_Handler();
    }
    /* USER CODE BEGIN ADC1_Init 2 */

    /* USER CODE END ADC1_Init 2 */

}

/**
 * @brief DAC1 Initialization Function
 * @param None
 * @retval None
 */
static void MX_DAC1_Init(void)
{

    /* USER CODE BEGIN DAC1_Init 0 */

    /* USER CODE END DAC1_Init 0 */

    DAC_ChannelConfTypeDef sConfig = {0};

    /* USER CODE BEGIN DAC1_Init 1 */

    /* USER CODE END DAC1_Init 1 */

    /** DAC Initialization
     */
    hdac1.Instance = DAC1;
    if (HAL_DAC_Init(&hdac1) != HAL_OK)
    {
        Error_Handler();
    }

    /** DAC channel OUT1 config
     */
    sConfig.DAC_SampleAndHold = DAC_SAMPLEANDHOLD_DISABLE;
    sConfig.DAC_Trigger = DAC_TRIGGER_NONE;
    sConfig.DAC_OutputBuffer = DAC_OUTPUTBUFFER_DISABLE;
    sConfig.DAC_ConnectOnChipPeripheral = DAC_CHIPCONNECT_DISABLE;
    sConfig.DAC_UserTrimming = DAC_TRIMMING_FACTORY;
    if (HAL_DAC_ConfigChannel(&hdac1, &sConfig, DAC_CHANNEL_1) != HAL_OK)
    {
        Error_Handler();
    }

    /** DAC channel OUT2 config
     */
    if (HAL_DAC_ConfigChannel(&hdac1, &sConfig, DAC_CHANNEL_2) != HAL_OK)
    {
        Error_Handler();
    }
    /* USER CODE BEGIN DAC1_Init 2 */
    //    HAL_DACEx_SelfCalibrate(&hdac1, &sConfig, DAC_CHANNEL_1);
    //    HAL_DACEx_SelfCalibrate(&hdac1, &sConfig, DAC_CHANNEL_2);
    /* USER CODE END DAC1_Init 2 */

}

/**
 * @brief I2C1 Initialization Function
 * @param None
 * @retval None
 */
static void MX_I2C1_Init(void)
{

    /* USER CODE BEGIN I2C1_Init 0 */

    /* USER CODE END I2C1_Init 0 */

    /* USER CODE BEGIN I2C1_Init 1 */

    /* USER CODE END I2C1_Init 1 */
    hi2c1.Instance = I2C1;
    hi2c1.Init.Timing = 0x00702991;
    hi2c1.Init.OwnAddress1 = 0;
    hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
    hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
    hi2c1.Init.OwnAddress2 = 0;
    hi2c1.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
    hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
    hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
    if (HAL_I2C_Init(&hi2c1) != HAL_OK)
    {
        Error_Handler();
    }

    /** Configure Analogue filter
     */
    if (HAL_I2CEx_ConfigAnalogFilter(&hi2c1, I2C_ANALOGFILTER_ENABLE) != HAL_OK)
    {
        Error_Handler();
    }

    /** Configure Digital filter
     */
    if (HAL_I2CEx_ConfigDigitalFilter(&hi2c1, 0) != HAL_OK)
    {
        Error_Handler();
    }
    /* USER CODE BEGIN I2C1_Init 2 */

    /* USER CODE END I2C1_Init 2 */

}

/**
 * @brief I2C3 Initialization Function
 * @param None
 * @retval None
 */
static void MX_I2C3_Init(void)
{

    /* USER CODE BEGIN I2C3_Init 0 */

    /* USER CODE END I2C3_Init 0 */

    /* USER CODE BEGIN I2C3_Init 1 */

    /* USER CODE END I2C3_Init 1 */
    hi2c3.Instance = I2C3;
    hi2c3.Init.Timing = 0x0070228A;
    hi2c3.Init.OwnAddress1 = 0;
    hi2c3.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
    hi2c3.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
    hi2c3.Init.OwnAddress2 = 0;
    hi2c3.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
    hi2c3.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
    hi2c3.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
    if (HAL_I2C_Init(&hi2c3) != HAL_OK)
    {
        Error_Handler();
    }

    /** Configure Analogue filter
     */
    if (HAL_I2CEx_ConfigAnalogFilter(&hi2c3, I2C_ANALOGFILTER_ENABLE) != HAL_OK)
    {
        Error_Handler();
    }

    /** Configure Digital filter
     */
    if (HAL_I2CEx_ConfigDigitalFilter(&hi2c3, 7) != HAL_OK)
    {
        Error_Handler();
    }
    /* USER CODE BEGIN I2C3_Init 2 */

    /* USER CODE END I2C3_Init 2 */

}

/**
 * @brief TIM2 Initialization Function
 * @param None
 * @retval None
 */
static void MX_TIM2_Init(void)
{

    /* USER CODE BEGIN TIM2_Init 0 */

    /* USER CODE END TIM2_Init 0 */

    TIM_ClockConfigTypeDef sClockSourceConfig = {0};
    TIM_MasterConfigTypeDef sMasterConfig = {0};

    /* USER CODE BEGIN TIM2_Init 1 */

    /* USER CODE END TIM2_Init 1 */
    htim2.Instance = TIM2;
    htim2.Init.Prescaler = 79;
    htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
    htim2.Init.Period = 99999;
    htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
    if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
    {
        Error_Handler();
    }
    sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
    if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
    {
        Error_Handler();
    }
    sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
    sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
    if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
    {
        Error_Handler();
    }
    /* USER CODE BEGIN TIM2_Init 2 */

    /* USER CODE END TIM2_Init 2 */

}

/**
 * @brief TIM6 Initialization Function
 * @param None
 * @retval None
 */
static void MX_TIM6_Init(void)
{

    /* USER CODE BEGIN TIM6_Init 0 */

    /* USER CODE END TIM6_Init 0 */

    TIM_MasterConfigTypeDef sMasterConfig = {0};

    /* USER CODE BEGIN TIM6_Init 1 */

    /* USER CODE END TIM6_Init 1 */
    htim6.Instance = TIM6;
    htim6.Init.Prescaler = 79;
    htim6.Init.CounterMode = TIM_COUNTERMODE_UP;
    htim6.Init.Period = 65535;
    htim6.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
    if (HAL_TIM_Base_Init(&htim6) != HAL_OK)
    {
        Error_Handler();
    }
    sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
    sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
    if (HAL_TIMEx_MasterConfigSynchronization(&htim6, &sMasterConfig) != HAL_OK)
    {
        Error_Handler();
    }
    /* USER CODE BEGIN TIM6_Init 2 */

    /* USER CODE END TIM6_Init 2 */

}

/**
 * @brief TIM7 Initialization Function
 * @param None
 * @retval None
 */
static void MX_TIM7_Init(void)
{

    /* USER CODE BEGIN TIM7_Init 0 */

    /* USER CODE END TIM7_Init 0 */

    TIM_MasterConfigTypeDef sMasterConfig = {0};

    /* USER CODE BEGIN TIM7_Init 1 */

    /* USER CODE END TIM7_Init 1 */
    htim7.Instance = TIM7;
    htim7.Init.Prescaler = 39999;
    htim7.Init.CounterMode = TIM_COUNTERMODE_UP;
    htim7.Init.Period = 199;
    htim7.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
    if (HAL_TIM_Base_Init(&htim7) != HAL_OK)
    {
        Error_Handler();
    }
    sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
    sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
    if (HAL_TIMEx_MasterConfigSynchronization(&htim7, &sMasterConfig) != HAL_OK)
    {
        Error_Handler();
    }
    /* USER CODE BEGIN TIM7_Init 2 */

    /* USER CODE END TIM7_Init 2 */

}

/**
 * @brief USART2 Initialization Function
 * @param None
 * @retval None
 */
static void MX_USART2_UART_Init(void)
{

    /* USER CODE BEGIN USART2_Init 0 */

    /* USER CODE END USART2_Init 0 */

    /* USER CODE BEGIN USART2_Init 1 */

    /* USER CODE END USART2_Init 1 */
    huart2.Instance = USART2;
    huart2.Init.BaudRate = 115200;
    huart2.Init.WordLength = UART_WORDLENGTH_8B;
    huart2.Init.StopBits = UART_STOPBITS_1;
    huart2.Init.Parity = UART_PARITY_NONE;
    huart2.Init.Mode = UART_MODE_TX_RX;
    huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    huart2.Init.OverSampling = UART_OVERSAMPLING_16;
    huart2.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
    huart2.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
    if (HAL_UART_Init(&huart2) != HAL_OK)
    {
        Error_Handler();
    }
    /* USER CODE BEGIN USART2_Init 2 */

    /* USER CODE END USART2_Init 2 */

}

/**
 * Enable DMA controller clock
 */
static void MX_DMA_Init(void)
{

    /* DMA controller clock enable */
    __HAL_RCC_DMA1_CLK_ENABLE();

    /* DMA interrupt init */
    /* DMA1_Channel1_IRQn interrupt configuration */
    HAL_NVIC_SetPriority(DMA1_Channel1_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(DMA1_Channel1_IRQn);

}

/**
 * @brief GPIO Initialization Function
 * @param None
 * @retval None
 */
static void MX_GPIO_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    /* GPIO Ports Clock Enable */
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();

    /*Configure GPIO pin Output Level */
    HAL_GPIO_WritePin(GPIOA, LCD_RST_Pin|MUX_SEL_Pin, GPIO_PIN_RESET);

    /*Configure GPIO pins : LCD_RST_Pin MUX_SEL_Pin */
    GPIO_InitStruct.Pin = LCD_RST_Pin|MUX_SEL_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /*Configure GPIO pins : BTN_DOWN_Pin BTN_OK_Pin JOY_PRESS_Pin JOY_UP_Pin
                           JOY_DOWN_Pin JOY_LEFT_Pin */
    GPIO_InitStruct.Pin = BTN_DOWN_Pin|BTN_OK_Pin|JOY_PRESS_Pin|JOY_UP_Pin
            |JOY_DOWN_Pin|JOY_LEFT_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    /*Configure GPIO pins : BTN_UP_Pin JOY_RIGHT_Pin */
    GPIO_InitStruct.Pin = BTN_UP_Pin|JOY_RIGHT_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /* EXTI interrupt init*/
    HAL_NVIC_SetPriority(EXTI0_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(EXTI0_IRQn);

    HAL_NVIC_SetPriority(EXTI1_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(EXTI1_IRQn);

    HAL_NVIC_SetPriority(EXTI3_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(EXTI3_IRQn);

    HAL_NVIC_SetPriority(EXTI9_5_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);

    HAL_NVIC_SetPriority(EXTI15_10_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);

}

/* USER CODE BEGIN 4 */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin){
    buttonDesc.gpioPin = GPIO_Pin;

    switch(GPIO_Pin){
    case BTN_UP_Pin:
        buttonDesc.buttonEvent = BTN_UP;
        buttonDesc.gpioPort = BTN_UP_GPIO_Port;
        break;
    case BTN_OK_Pin:
        buttonDesc.buttonEvent = BTN_OK;
        buttonDesc.gpioPort = BTN_OK_GPIO_Port;
        break;
    case BTN_DOWN_Pin:
        buttonDesc.buttonEvent = BTN_DOWN;
        buttonDesc.gpioPort = BTN_DOWN_GPIO_Port;
        break;
    case JOY_UP_Pin:
        buttonDesc.buttonEvent = JOY_UP;
        buttonDesc.gpioPort = JOY_UP_GPIO_Port;
        break;
    case JOY_PRESS_Pin:
        buttonDesc.buttonEvent = JOY_PRESS;
        buttonDesc.gpioPort = JOY_PRESS_GPIO_Port;
        break;
    case JOY_DOWN_Pin:
        buttonDesc.buttonEvent = JOY_DOWN;
        buttonDesc.gpioPort = JOY_DOWN_GPIO_Port;
        break;
    case JOY_LEFT_Pin:
        buttonDesc.buttonEvent = JOY_LEFT;
        buttonDesc.gpioPort = JOY_LEFT_GPIO_Port;
        break;
    case JOY_RIGHT_Pin:
        buttonDesc.buttonEvent = JOY_RIGHT;
        buttonDesc.gpioPort = JOY_RIGHT_GPIO_Port;
        break;
    default:
        buttonDesc.buttonEvent = BTN_NONE;
        buttonDesc.gpioPin = BTN_NONE;
        buttonDesc.gpioPort = NULL;
        return; // avoid to start the timer
    }

    HAL_TIM_Base_Start_IT(&htim7);

    return;
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
    if(htim->Instance == TIM7){
        HAL_TIM_Base_Stop_IT(htim);
        htim->Instance->CNT = 0;

        if(buttonDesc.buttonEvent != BTN_NONE &&
                HAL_GPIO_ReadPin(buttonDesc.gpioPort, buttonDesc.gpioPin) == GPIO_PIN_RESET){
            buttonPressed = buttonDesc.buttonEvent;
            buttonDesc.buttonEvent = BTN_NONE;
        }
    }

    if(htim->Instance == TIM2){
        dacIndex = (~dacIndex) & 1;
        HAL_GPIO_TogglePin(MUX_SEL_GPIO_Port, MUX_SEL_Pin);
        HAL_DAC_SetValue(&hdac1, DAC_CHANNEL_2, DAC_ALIGN_12B_R, angToDAC[dacIndex]);
        HAL_DAC_SetValue(&hdac1, DAC_CHANNEL_1, DAC_ALIGN_12B_R, distToDAC);
        sh1106_UpdateScreen();
    }

}

static VL53L1X_ERROR initVL53L1X(void){
    uint8_t sensorState=0;
    VL53L1X_ERROR status=VL53L1_ERROR_NONE;

    status = VL53L1X_BootState(vl53l1xDev, &sensorState);

    HAL_Delay(2);

    if(status == VL53L1_ERROR_NONE)
        printf("VL53L1X booted\n");
    else{
        printf("VL53L1X not present!\n");
        return -1;
    }

    status = VL53L1X_SensorInit(vl53l1xDev);
    if(status == VL53L1_ERROR_NONE)
        printf("VL53L1X initialized\n");
    else{
        printf("VL53L1X not present!\n");
        return -1;
    }
    status = VL53L1X_SetDistanceMode(vl53l1xDev, 2);
    status = VL53L1X_SetTimingBudgetInMs(vl53l1xDev, 500);
    status = VL53L1X_SetInterMeasurementInMs(vl53l1xDev, 500);

    return status;
}

static void msgPrinter(int level, const char * str, va_list ap){
    vprintf(str, ap);
    printf("\r\n");
}

static inv_device_t* initICM20948(void){
    inv_device_t* device;
    int rc = 0;
    int accelFSR = 2;
    int gyroFSR = 250;

    inv_device_icm20948_init2(&imu,
                              get_serif_inst_i2c(),
                              &sensor_listener,
                              dmp3_image,
                              sizeof(dmp3_image));

    device = inv_device_icm20948_get_base(&imu);

    inv_device_icm20948_reset(device);

    rc = inv_device_icm20948_set_sensor_config(&imu,
                                               INV_SENSOR_TYPE_ACCELEROMETER,
                                               INV_DEVICE_ICM20948_CONFIG_FSR,
                                               (const void*)&accelFSR,
                                               0);
    check_rc(rc);

    rc = inv_device_icm20948_set_sensor_config(&imu,
                                               INV_SENSOR_TYPE_GYROSCOPE,
                                               INV_DEVICE_ICM20948_CONFIG_FSR,
                                               (const void*)&gyroFSR,
                                               0);
    check_rc(rc);

    inv_icm20948_set_lowpower_or_highperformance(&(imu.icm20948_states), 1);

    //    rc = inv_device_icm20948_set_sensor_config(&imu,
    //            INV_SENSOR_TYPE_ACCELEROMETER,
    //            INV_DEVICE_ICM20948_CONFIG_OFFSET,
    //            (const void*)&accelBias,
    //            0);
    //    check_rc(rc);
    //
    //    rc = inv_device_icm20948_set_sensor_config(&imu,
    //            INV_SENSOR_TYPE_GYROSCOPE,
    //            INV_DEVICE_ICM20948_CONFIG_OFFSET,
    //            (const void*)&gyroBias,
    //            0);
    //    check_rc(rc);

    rc  = inv_device_set_sensor_period_us(device, INV_SENSOR_TYPE_ACCELEROMETER, 50000);
    check_rc(rc);
    rc  = inv_device_set_sensor_period_us(device, INV_SENSOR_TYPE_GYROSCOPE, 50000);
    check_rc(rc);
    rc  = inv_device_set_sensor_period_us(device, INV_SENSOR_TYPE_MAGNETOMETER, 50000);
    check_rc(rc);
    rc  = inv_device_set_sensor_period_us(device, INV_SENSOR_TYPE_ROTATION_VECTOR, 50000);
    //    rc  = inv_device_set_sensor_period_us(device, INV_SENSOR_TYPE_ORIENTATION, 50000);
    check_rc(rc);

    rc = inv_device_start_sensor(device, INV_SENSOR_TYPE_ACCELEROMETER);
    check_rc(rc);
    rc = inv_device_start_sensor(device, INV_SENSOR_TYPE_GYROSCOPE);
    check_rc(rc);
    rc = inv_device_start_sensor(device, INV_SENSOR_TYPE_MAGNETOMETER);
    check_rc(rc);
    rc = inv_device_start_sensor(device, INV_SENSOR_TYPE_ROTATION_VECTOR);
    //    rc = inv_device_start_sensor(device, INV_SENSOR_TYPE_ORIENTATION);
    check_rc(rc);

    return device;
}

static void check_rc(int rc){
    if(rc == -1) {
        INV_MSG(INV_MSG_LEVEL_INFO, "BAD RC=%d\r\n", rc);
        while(1);
    }
}

static void sensor_event_cb(const inv_sensor_event_t * event, void * arg){
    (void)arg;

    float q[4] = {0.0, 0.0, 0.0, 0.0};

    if(event->status == INV_SENSOR_STATUS_DATA_UPDATED &&
            INV_SENSOR_ID_TO_TYPE(event->sensor) == INV_SENSOR_TYPE_ROTATION_VECTOR){

        q[0] = event->data.quaternion.quat[0];
        q[1] = event->data.quaternion.quat[1];
        q[2] = event->data.quaternion.quat[2];
        q[3] = event->data.quaternion.quat[3];

        acc = event->data.quaternion.accuracy_flag;

        theta = atan2(2*((q[0]*q[1])+(q[2]*q[3])),1-(2*(pow(q[1],2)+pow(q[2],2))));//*M_1_PI*180;
        phi = atan2(2*((q[0]*q[3])+(q[1]*q[2])),1-(2*(pow(q[2],2)+pow(q[3],2))));//*M_1_PI*180;

//        phi = atan2(2*((q[0]*q[1])+(q[2]*q[3])),1-(2*(pow(q[1],2)+pow(q[2],2))));//*M_1_PI*180;
//        theta = asin(2*((q[0]*q[2])-(q[3]*q[1])));//*M_1_PI*180;
//        psi = atan2(2*((q[0]*q[3])+(q[1]*q[2])),1-(2*(pow(q[2],2)+pow(q[3],2))));//*M_1_PI*180;

        if(theta <= -M_PI_2)
            angToDAC[THETA_IDX] = 0;
        else if(theta >= 0)
            angToDAC[THETA_IDX] = 4095;
        else
            angToDAC[THETA_IDX] = (theta+M_PI_2)*M_2_PI*4095;

        angToDAC[PHI_IDX] = (phi >= 0) ?
                phi*M_1_PI*2047 : (phi+(2*M_PI))*M_1_PI*2047;

//        angToDAC[THETA_IDX] = (theta >= 0) ?
//                theta*M_1_PI(theta+M_PI)*M_1_PI*0.5*4095;
//        angToDAC[PHI_IDX] = (phi+M_PI)*M_1_PI*0.5*4095;

        angToLCD[THETA_IDX] = (theta+M_PI_2)*M_2_PI*90;
        angToLCD[PHI_IDX] = (phi >= 0) ?
                phi*M_1_PI*180 : (phi+(2*M_PI))*M_1_PI*180;

//        angToLCD[THETA_IDX] = (theta >= 0) ?
//                theta*M_1_PI*180 : (theta+(2*M_PI))*M_1_PI*180;
//        angToLCD[PHI_IDX] = (phi >= 0) ?
//                phi*M_1_PI*180 : (phi+(2*M_PI))*M_1_PI*180;
    }

    //            if(event->status == INV_SENSOR_STATUS_DATA_UPDATED &&
    //               INV_SENSOR_ID_TO_TYPE(event->sensor) == INV_SENSOR_TYPE_ORIENTATION){
    //                a[0] = event->data.orientation.x;
    //                a[1] = event->data.orientation.y;
    //                a[2] = event->data.orientation.z;
    //            }

}

static uint8_t selectScreen(uint8_t btn, uint8_t currScreen){
    switch(btn){
    case BTN_UP:
        return HOME_SCR;
    case BTN_OK:
        return CONFIG_SCR;
    case BTN_DOWN:
        return INFO_SCR;
    default:
        return currScreen;
    }
}

static void homeAuxFunc(void* arg){
    char distStr[10] = "";
    char thetaStr[10] = "";
    char phiStr[10] = "";
    char thetaPadding[5] = "";
    char phiPadding[5] = "";
    uint8_t titlePos = 0;
    uint8_t measPos = 0;

    snprintf(distStr,100," = %.3fm",((float)dist/1000.0));
    snprintf(thetaStr,100," = %3.1f",angToLCD[THETA_IDX]);
    snprintf(phiStr,100," = %3.1f",angToLCD[PHI_IDX]);

    snprintf(thetaPadding,5,"%*s",10-strlen(thetaStr)," ");
    snprintf(phiPadding,5,"%*s",10-strlen(phiStr)," ");

    sh1106_SetCursor(30, titlePos);
    sh1106_WriteString("Measurements", Font_7x10, White);

    measPos = titlePos + 20;

    sh1106_SetCursor(30, measPos);
    sh1106_WriteString("D", Font_7x10, White);
    sh1106_SetCursor(37,measPos);
    sh1106_WriteString(distStr, Font_7x10, White);

    measPos += 10;

    sh1106_SetCursor(30, measPos);
    sh1106_WriteChar(THETA, cFont_7x10, White);
    sh1106_SetCursor(37,measPos);
    sh1106_WriteString(thetaStr, Font_7x10, White);
    sh1106_WriteChar(DEG, cFont_7x10, White);
    sh1106_WriteString(thetaPadding, Font_7x10, White);

    measPos += 10;

    sh1106_SetCursor(30, measPos);
    sh1106_WriteChar(PHI, cFont_7x10, White);
    sh1106_SetCursor(37,measPos);
    sh1106_WriteString(phiStr, Font_7x10, White);
    sh1106_WriteChar(DEG, cFont_7x10, White);
    sh1106_WriteString(phiPadding, Font_7x10, White);
}

static void updateCursor(uint8_t cursorPos){
    for(int i = CFG_DCAL_POS; i <= CFG_SAVE_POS; i += CFG_OFF_POS){
        sh1106_SetCursor(25, i);

        if(i == cursorPos)
            sh1106_WriteString(">", Font_6x8, White);
        else
            sh1106_WriteString(" ", Font_6x8, White);
    }
}

static void configAuxFunc(void* arg){
    cfgScreenArg_t* cfgArg = (cfgScreenArg_t*)arg;

    sh1106_SetCursor(22, 0);
    sh1106_WriteString("Configurations", Font_7x10, White);

    sh1106_SetCursor(35, CFG_DCAL_POS);
    sh1106_WriteString("Dist. calib.", Font_6x8, White);

    sh1106_SetCursor(35, CFG_ACAL_POS);
    sh1106_WriteString("Ang. calib.", Font_6x8, White);

    sh1106_SetCursor(35, CFG_SAVE_POS);
    sh1106_WriteString("Save in flash", Font_6x8, White);

    updateCursor(cfgArg->cursorPos);
}

static void infoAuxFunc(){
    uint8_t titlePos = 0;

    sh1106_SetCursor(57, titlePos);
    sh1106_WriteString("Info", Font_7x10, White);

    sh1106_SetCursor(30,10);
    sh1106_WriteString("PicoBarn", Font_11x18, White);

    sh1106_SetCursor(30,30);
    sh1106_WriteString("support:", Font_7x10, White);

    sh1106_SetCursor(25,45);
    sh1106_WriteString("info@picobarn.it", Font_6x8, White);
}

static void calibrateVL53L1X(){
    int16_t distOffset = 0;

    sh1106_SetCursor(30, 0);
    sh1106_WriteString("Dist. calib.", Font_7x10, White);

    sh1106_SetCursor(35,30);
    sh1106_WriteString("Calibrating...", Font_6x8, White);

    VL53L1X_StopRanging(vl53l1xDev);
    while(VL53L1X_CalibrateOffset(vl53l1xDev, 140, &distOffset)){}
    VL53L1X_SetOffset(vl53l1xDev,distOffset);
    VL53L1X_StartRanging(vl53l1xDev);

    return;
}

static void calibrateICM20948(){
    int selfTestRes = 0;

    sh1106_SetCursor(37, 0);
    sh1106_WriteString("Ang. calib.", Font_7x10, White);

    sh1106_SetCursor(35,30);
    sh1106_WriteString("Calibrating...", Font_6x8, White);

    if(imu.icm20948_states.selftest_done != 1){
        selfTestRes = inv_icm20948_run_selftest(&(imu.icm20948_states));

        if(selfTestRes == 7){
            printf("Self Test OK\r\n");
            printf("GYRO: %d %d %d\r\n",
                   imu.icm20948_states.gyro_st_data[0],
                   imu.icm20948_states.gyro_st_data[1],
                   imu.icm20948_states.gyro_st_data[2]);
            printf("ACCEL: %d %d %d\r\n",
                   imu.icm20948_states.accel_st_data[0],
                   imu.icm20948_states.accel_st_data[1],
                   imu.icm20948_states.accel_st_data[2]);

            imu.icm20948_states.selftest_done = 1;
        }
    }
}

static void saveInFlash(){

}

static void confFunc(uint8_t cursorPos){
    sh1106_Fill(Black);
    sh1106_DrawBitmap(0, 0, screens[CONFIG_SCR].bitmap, 128, 64, White);

    switch(cursorPos){
    case CFG_DCAL_POS:
        calibrateVL53L1X();
        break;
    case CFG_ACAL_POS:
        calibrateICM20948();
        break;
    case CFG_SAVE_POS:
        saveInFlash();
        break;
    }

    sh1106_Fill(Black);
    sh1106_DrawBitmap(0, 0, screens[CONFIG_SCR].bitmap, 128, 64, White);

    return;
}

static void joyParseFunc(void* arg){
    cfgScreenArg_t* cfgArg = (cfgScreenArg_t*)arg;
    uint8_t curPos = cfgArg->cursorPos;

    switch(cfgArg->btnPressed){
    case JOY_UP:
        cfgArg->cursorPos = (curPos == CFG_DCAL_POS) ?
                CFG_SAVE_POS : curPos - CFG_OFF_POS;
        break;
    case JOY_PRESS:
        confFunc(curPos);
        break;
    case JOY_DOWN:
        cfgArg->cursorPos = (curPos == CFG_SAVE_POS) ?
                CFG_DCAL_POS : curPos + CFG_OFF_POS;
        break;
    case JOY_LEFT:
        break;
    case JOY_RIGHT:
        break;
    default:
        cfgArg->cursorPos = curPos;
    }

    cfgArg->btnPressed = BTN_NONE;

    return;
}

static void noop(void* arg){
    return;
}
/* USER CODE END 4 */

/**
 * @brief  This function is executed in case of error occurrence.
 * @retval None
 */
void Error_Handler(void)
{
    /* USER CODE BEGIN Error_Handler_Debug */
    /* User can add his own implementation to report the HAL error return state */
    __disable_irq();
    while (1)
    {
    }
    /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
 * @brief  Reports the name of the source file and the source line number
 *         where the assert_param error has occurred.
 * @param  file: pointer to the source file name
 * @param  line: assert_param error line source number
 * @retval None
 */
void assert_failed(uint8_t *file, uint32_t line)
{
    /* USER CODE BEGIN 6 */
    /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
    /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
