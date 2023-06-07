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
#include "fatfs.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "Invn/Devices/DeviceIcm20948.h"
#include "Invn/EmbUtils/Message.h"
#include "I2CSerifHal.h"
#include "timerDelay.h"
#include <math.h>
#include <stdio.h>
#include "retarget.h"
#include "vl53l1x_api.h"
#include "vl53l1x_calibration.h"
#include "vl53l1_error_codes.h"
#include "screen.h"
#include "filesLib.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define DIST_SAMPLES 10
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
ADC_HandleTypeDef hadc1;
DMA_HandleTypeDef hdma_adc1;

DAC_HandleTypeDef hdac1;

I2C_HandleTypeDef hi2c1;

SPI_HandleTypeDef hspi1;
DMA_HandleTypeDef hdma_spi1_tx;

TIM_HandleTypeDef htim2;
TIM_HandleTypeDef htim6;
TIM_HandleTypeDef htim16;

UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_ADC1_Init(void);
static void MX_I2C1_Init(void);
static void MX_DMA_Init(void);
static void MX_TIM6_Init(void);
static void MX_DAC1_Init(void);
static void MX_TIM2_Init(void);
static void MX_SPI1_Init(void);
static void MX_TIM16_Init(void);
/* USER CODE BEGIN PFP */
static void initDACZero(void);
static float updateMean(uint16_t dist, uint16_t* distArr, uint32_t distArrLen);
static inv_device_t* initICM20948(void);
static VL53L1X_ERROR initVL53L1X(void);
static void msgPrinter(int level, const char * str, va_list ap);
static void sensor_event_cb(const inv_sensor_event_t * event, void * arg);
void check_rc(int rc);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
static const uint8_t dmp3_image[] = {
#include "Invn/Images/icm20948_img.dmp3a.h"
};
inv_device_icm20948_t imu;
static const inv_sensor_listener_t sensor_listener = {sensor_event_cb, 0};
uint16_t vl53l1xDev = 0x52;
float q[4] = {0.0, 0.0, 0.0, 0.0};
float a[4] = {0.0, 0.0, 0.0, 0.0};
//float g[4] = {0.0, 0.0, 0.0, 0.0};
float m[4] = {0.0, 0.0, 0.0, 0.0};
uint8_t aQ = 0;
uint8_t aA = 0;
//uint8_t aG = 0;
uint8_t aM = 0;
volatile float phi = 0.0, theta = 0.0, psi = 0.0;
volatile float phiRel = 0.0, thetaRel = 0.0, psiRel = 0.0;
volatile float phiZero = 0.0, thetaZero = 0.0;
uint16_t dist = 0;
int16_t distOffset = 0;
int16_t distXtalk = 0;
volatile uint32_t distToDAC = 0;
volatile uint32_t angToDAC[2] = { 0, 0 };
volatile float angToLCD[2] = { 0.0, 0.0 };
volatile float distToDisp = 0.0;
volatile uint8_t dacIndex = 0;
uint8_t distStatus = 0;
uint8_t distPresent = 0;
uint8_t sdMounted = 0;
uint8_t logEnabled = 0;
uint8_t screenOrient = DISP_ORIENTATION;
screen_t menu;
FIL tileFile;
FIL barFile;
uint8_t imgBuf[BAR_SIZE];
char logStr[LOGSTR_LEN] = "";
char uartStr[UARTSTR_LEN] = "";
char timeStr[TIMESTR_LEN] = "";
volatile uint8_t hours = 0, minutes = 0, seconds = 0;
volatile uint8_t dumpLogEnabled = 0;
volatile uint8_t acqPaused = 0;
volatile uint8_t monitorEnabled = 1;
uint32_t config[CFG_WORDS] = {0, 0, 0, 0, 0};
uint32_t defConfig[CFG_WORDS] = {0, 0, 0, ILI9341_ROTATION_R};
volatile int32_t zeroFeedback[2] = {0, 0};
uint32_t adcData = 0;
uint8_t distDataReady = 0;
volatile float vref = 0.0;
volatile uint16_t* vrefCal = (uint16_t*)VREFINTCAL_ADDR;
volatile uint8_t dacConverted = 0;
uint16_t distArray[DIST_SAMPLES];
volatile uint16_t distMode = VL53L1X_SHORT_DIST_MODE;
uint8_t rangeStatus = 0;

/* USER CODE END 0 */

/**
 * @brief  The application entry point.
 * @retval int
 */
int main(void)
{
    /* USER CODE BEGIN 1 */
    int rc = 0;
    inv_device_t* device;
    uint8_t distStatus = 0;

    FATFS FatFs;
    FRESULT fres;

    uint16_t touchX = 0;
    uint16_t touchY = 0;
    uint16_t dispX = 0;
    uint16_t dispY = 0;
    uint8_t zone = HOME;
    bool validCoord;
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
    MX_DMA_Init();
    MX_TIM6_Init();
    MX_DAC1_Init();
    MX_TIM2_Init();
    MX_SPI1_Init();
    MX_FATFS_Init();
    MX_TIM16_Init();
    /* USER CODE BEGIN 2 */
    RetargetInit(&huart2);

    memset(distArray, 0, DIST_SAMPLES*sizeof(uint16_t));

    ILI9341_Unselect();
    ILI9341_TouchUnselect();
    ILI9341_Init();

    HAL_Delay(1000);

    fres = f_mount(&FatFs, "", 1);
    if(fres != FR_OK){
        printf("Cannot mount SD card...\n");
        sdMounted = 0;
        ILI9341_SetOrientation(screenOrient);
    }else{
        sdMounted = 1;
    }

    printf("PICOBARN\nLoading...\n");

    INV_MSG_SETUP(INV_MSG_LEVEL_MAX,msgPrinter);

    printf("Starting distance sensor...\n");

    distStatus = initVL53L1X();

    if(distStatus != -1){
        printf("Start ranging...\n");
        VL53L1X_StartRanging(vl53l1xDev);
        printf("Ranging started!\n");
    }else
        printf("Cannot start ranging...\n");

    printf("Starting 9 axis IMU...\n");

    device = initICM20948();

    HAL_TIM_Base_Start(&htim6);
    HAL_TIM_Base_Start_IT(&htim2);
    HAL_TIM_Base_Start_IT(&htim16);

    HAL_DAC_Start(&hdac1, DAC1_CHANNEL_1);
    HAL_DAC_Start(&hdac1, DAC1_CHANNEL_2);

    initDACZero();

    printf("All started, ready to go\n");

    if(sdMounted){
        readConfig(config);
        memcpy((void*)&distOffset, (void*)&config[DISTCAL_IDX], sizeof(uint16_t));
        memcpy((void*)&thetaZero, (void*)&config[THETAZERO_IDX], sizeof(float));
        memcpy((void*)&phiZero, (void*)&config[PHIZERO_IDX], sizeof(float));
        memcpy((void*)&screenOrient, (void*)&config[SORIENT_IDX], sizeof(uint8_t));
        memcpy((void*)&distXtalk, (void*)&config[DISTXTALK_IDX], sizeof(uint16_t));

        VL53L1X_StopRanging(vl53l1xDev);
        VL53L1X_SetOffset(vl53l1xDev,distOffset);
        VL53L1X_SetXtalk(vl53l1xDev, distXtalk);
        VL53L1X_StartRanging(vl53l1xDev);

        f_open(&barFile, "bar.bmp", FA_READ);
        f_open(&tileFile, "tls.bmp", FA_READ);

        ILI9341_SetOrientation(screenOrient);

        drawBar(&barFile, imgBuf);

        resetLog();
    }

    initScreen(&menu);

    /* USER CODE END 2 */

    /* Infinite loop */
    /* USER CODE BEGIN WHILE */
    while (1)
    {
        /* USER CODE END WHILE */

        /* USER CODE BEGIN 3 */

        memset(timeStr, '\0', TIMESTR_LEN);
        snprintf(timeStr, TIMESTR_LEN, "[%02d:%02d:%02d]", hours, minutes, seconds);

        if(ILI9341_TouchPressed()){
            validCoord = ILI9341_TouchGetCoordinates(&touchX, &touchY);

            transformCoord(touchX, touchY, &dispX, &dispY, screenOrient, validCoord);

            zone = getZonePressed(dispX, dispY);

            updateScreen(&menu, zone);
        }

        menu.screenFuncPtr();

        if(!acqPaused){
            float distMean = 0.0;

            if(distStatus != -1){
                VL53L1X_CheckForDataReady(vl53l1xDev, &distDataReady);
                if(distDataReady == 1){
                    distDataReady = 0;

                    VL53L1X_GetDistance(vl53l1xDev, &dist);
                    VL53L1X_GetRangeStatus(vl53l1xDev, &rangeStatus);

                    distMean = updateMean(dist, distArray, DIST_SAMPLES);

                    if(dist < DIST_MODE_THRESHOLD && (distMode == VL53L1X_LONG_DIST_MODE)){
                        distMode = VL53L1X_SHORT_DIST_MODE;
                        VL53L1X_StopRanging(vl53l1xDev);
                        VL53L1X_SetDistanceMode(vl53l1xDev, distMode);
                        VL53L1X_StartRanging(vl53l1xDev);
                    }else if(dist > DIST_MODE_THRESHOLD && (distMode == VL53L1X_SHORT_DIST_MODE)){
                        distMode = VL53L1X_LONG_DIST_MODE;
                        VL53L1X_StopRanging(vl53l1xDev);
                        VL53L1X_SetDistanceMode(vl53l1xDev, distMode);
                        VL53L1X_StartRanging(vl53l1xDev);
                    }

                    distToDisp = distMean/1000.0;

                    distToDAC = (distMean >= VL53L1X_MAX_DISTANCE) ?
                            0 : DAC_MAX-((distMean*DAC_MAX)/VL53L1X_MAX_DISTANCE);
                }
            }

            rc = inv_device_poll(device);
            check_rc(rc);

            snprintf(uartStr, UARTSTR_LEN,
                     "$phi=%03.2f,theta=%03.2f,dist=%01.3f,"
                     "q0=%03.2f,q1=%03.2f,q2=%03.2f,q3=%03.2f,"
                     "ax=%03.2f,ay=%03.2f,az=%03.2f,"
//                     "gx=%03.2f,gy=%03.2f,gz=%03.2f,"
                     "mx=%03.2f,my=%03.2f,mz=%03.2f\n",
                     phi,theta,distToDisp,
                     q[0],q[1],q[2],q[3],
                     a[0],a[1],a[2],
//                     g[0],g[1],g[2],
                     m[0],m[1],m[2]);//,

            if(monitorEnabled)
                printf("%s",uartStr);
        }

        if(sdMounted && logEnabled){
            memset(logStr, '\0', LOGSTR_LEN);
            strncat(logStr, timeStr, TIMESTR_LEN);
            strncat(logStr, uartStr, UARTSTR_LEN);

            writeLog(logStr);
        }
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
    hadc1.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV4;
    hadc1.Init.Resolution = ADC_RESOLUTION_12B;
    hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
    hadc1.Init.ScanConvMode = ADC_SCAN_DISABLE;
    hadc1.Init.EOCSelection = ADC_EOC_SEQ_CONV;
    hadc1.Init.LowPowerAutoWait = DISABLE;
    hadc1.Init.ContinuousConvMode = DISABLE;
    hadc1.Init.NbrOfConversion = 1;
    hadc1.Init.DiscontinuousConvMode = DISABLE;
    hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
    hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
    hadc1.Init.DMAContinuousRequests = DISABLE;
    hadc1.Init.Overrun = ADC_OVR_DATA_OVERWRITTEN;
    hadc1.Init.OversamplingMode = DISABLE;
    if (HAL_ADC_Init(&hadc1) != HAL_OK)
    {
        Error_Handler();
    }

    /** Configure Regular Channel
     */
    sConfig.Channel = ADC_CHANNEL_VREFINT;
    sConfig.Rank = ADC_REGULAR_RANK_1;
    sConfig.SamplingTime = ADC_SAMPLETIME_640CYCLES_5;
    sConfig.SingleDiff = ADC_SINGLE_ENDED;
    sConfig.OffsetNumber = ADC_OFFSET_NONE;
    sConfig.Offset = 0;
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
    sConfig.DAC_OutputBuffer = DAC_OUTPUTBUFFER_ENABLE;
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
 * @brief SPI1 Initialization Function
 * @param None
 * @retval None
 */
static void MX_SPI1_Init(void)
{

    /* USER CODE BEGIN SPI1_Init 0 */

    /* USER CODE END SPI1_Init 0 */

    /* USER CODE BEGIN SPI1_Init 1 */

    /* USER CODE END SPI1_Init 1 */
    /* SPI1 parameter configuration*/
    hspi1.Instance = SPI1;
    hspi1.Init.Mode = SPI_MODE_MASTER;
    hspi1.Init.Direction = SPI_DIRECTION_2LINES;
    hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
    hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
    hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
    hspi1.Init.NSS = SPI_NSS_SOFT;
    hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_4;
    hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
    hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
    hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
    hspi1.Init.CRCPolynomial = 7;
    hspi1.Init.CRCLength = SPI_CRC_LENGTH_DATASIZE;
    hspi1.Init.NSSPMode = SPI_NSS_PULSE_ENABLE;
    if (HAL_SPI_Init(&hspi1) != HAL_OK)
    {
        Error_Handler();
    }
    /* USER CODE BEGIN SPI1_Init 2 */

    /* USER CODE END SPI1_Init 2 */

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
    htim2.Init.Period = 999;
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
 * @brief TIM16 Initialization Function
 * @param None
 * @retval None
 */
static void MX_TIM16_Init(void)
{

    /* USER CODE BEGIN TIM16_Init 0 */

    /* USER CODE END TIM16_Init 0 */

    /* USER CODE BEGIN TIM16_Init 1 */

    /* USER CODE END TIM16_Init 1 */
    htim16.Instance = TIM16;
    htim16.Init.Prescaler = 40000-1;
    htim16.Init.CounterMode = TIM_COUNTERMODE_UP;
    htim16.Init.Period = 2000-1;
    htim16.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    htim16.Init.RepetitionCounter = 0;
    htim16.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
    if (HAL_TIM_Base_Init(&htim16) != HAL_OK)
    {
        Error_Handler();
    }
    /* USER CODE BEGIN TIM16_Init 2 */

    /* USER CODE END TIM16_Init 2 */

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
    /* DMA1_Channel3_IRQn interrupt configuration */
    HAL_NVIC_SetPriority(DMA1_Channel3_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(DMA1_Channel3_IRQn);

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
    __HAL_RCC_GPIOC_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();

    /*Configure GPIO pin Output Level */
    HAL_GPIO_WritePin(GPIOA, LCD_RST_Pin|SD_CS_Pin|MUX_SEL_Pin, GPIO_PIN_RESET);

    /*Configure GPIO pin Output Level */
    HAL_GPIO_WritePin(GPIOB, TOUCH_CS_Pin|LCD_DC_Pin|LCD_CS_Pin, GPIO_PIN_RESET);

    /*Configure GPIO pin : ICM_INT_Pin */
    GPIO_InitStruct.Pin = ICM_INT_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(ICM_INT_GPIO_Port, &GPIO_InitStruct);

    /*Configure GPIO pin : DIST_INT_Pin */
    GPIO_InitStruct.Pin = DIST_INT_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(DIST_INT_GPIO_Port, &GPIO_InitStruct);

    /*Configure GPIO pins : LCD_RST_Pin SD_CS_Pin */
    GPIO_InitStruct.Pin = LCD_RST_Pin|SD_CS_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /*Configure GPIO pins : TOUCH_CS_Pin LCD_CS_Pin */
    GPIO_InitStruct.Pin = TOUCH_CS_Pin|LCD_CS_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    /*Configure GPIO pin : LCD_DC_Pin */
    GPIO_InitStruct.Pin = LCD_DC_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    HAL_GPIO_Init(LCD_DC_GPIO_Port, &GPIO_InitStruct);

    /*Configure GPIO pin : MUX_SEL_Pin */
    GPIO_InitStruct.Pin = MUX_SEL_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(MUX_SEL_GPIO_Port, &GPIO_InitStruct);

    /*Configure GPIO pin : TOUCH_IRQ_Pin */
    GPIO_InitStruct.Pin = TOUCH_IRQ_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(TOUCH_IRQ_GPIO_Port, &GPIO_InitStruct);

    /* EXTI interrupt init*/
    HAL_NVIC_SetPriority(EXTI15_10_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);

}

/* USER CODE BEGIN 4 */

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc)
{
    vref = *vrefCal*3.3/adcData;

    dacConverted = 1;
}


static void initDACZero(){
    // get vref
    HAL_ADC_Start_DMA(&hadc1, &adcData, 1);
    while(!dacConverted){}
    HAL_ADC_Stop_DMA(&hadc1);
}

static float updateMean(uint16_t dist, uint16_t* distArr, uint32_t distArrLen){
    float mean = 0.0;

    for(int i = 0; i < distArrLen-1; i++){
        distArr[i] = distArr[i+1];
    }

    distArr[distArrLen-1] = dist;

    for(int i = 0; i < distArrLen; i++)
        mean += (float)distArr[i];

    mean /= distArrLen;

    return mean;
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
    if(htim->Instance == TIM2 && !acqPaused){
        dacIndex = (~dacIndex) & 1;
        HAL_GPIO_TogglePin(MUX_SEL_GPIO_Port, MUX_SEL_Pin);
        HAL_DAC_SetValue(&hdac1, DAC_CHANNEL_2, DAC_ALIGN_12B_R,
                         angToDAC[1-dacIndex]);
        HAL_DAC_SetValue(&hdac1, DAC_CHANNEL_1, DAC_ALIGN_12B_R,
                         distToDAC);

    }else if(htim->Instance == TIM16){
        if(++seconds == 60){
            seconds = 0;
            minutes++;
        }

        if(minutes == 60){
            minutes = 0;
            hours++;
        }
    }
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    //    if(GPIO_Pin == ICM_INT_Pin){
    //        inv_device_t* device;
    //        int rc = 0;
    //
    //        device = inv_device_icm20948_get_base(&imu);
    //
    //        rc = inv_device_poll(device);
    //        check_rc(rc);
    //    }
}

static void msgPrinter(int level, const char * str, va_list ap){
    vprintf(str, ap);
    printf("\r\n");
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
    status = VL53L1X_SetDistanceMode(vl53l1xDev, distMode);
    status = VL53L1X_SetTimingBudgetInMs(vl53l1xDev, 50);
    status = VL53L1X_SetInterMeasurementInMs(vl53l1xDev, 50);
    status = VL53L1X_SetROI(vl53l1xDev, 6, 6);

    return status;
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

    rc  = inv_device_set_sensor_period_us(device, INV_SENSOR_TYPE_ACCELEROMETER, 50000);
    check_rc(rc);
//    rc  = inv_device_set_sensor_period_us(device, INV_SENSOR_TYPE_GYROSCOPE, 50000);
//    check_rc(rc);
    rc  = inv_device_set_sensor_period_us(device, INV_SENSOR_TYPE_MAGNETOMETER, 50000);
    check_rc(rc);
    rc  = inv_device_set_sensor_period_us(device, INV_SENSOR_TYPE_GEOMAG_ROTATION_VECTOR, 50000);
    check_rc(rc);

    rc = inv_device_start_sensor(device, INV_SENSOR_TYPE_ACCELEROMETER);
    check_rc(rc);
//    rc = inv_device_start_sensor(device, INV_SENSOR_TYPE_GYROSCOPE);
//    check_rc(rc);
    rc = inv_device_start_sensor(device, INV_SENSOR_TYPE_MAGNETOMETER);
    check_rc(rc);
    rc = inv_device_start_sensor(device, INV_SENSOR_TYPE_GEOMAG_ROTATION_VECTOR);
    check_rc(rc);

    return device;
}

void check_rc(int rc){
    if(rc == -1) {
        INV_MSG(INV_MSG_LEVEL_INFO, "BAD RC=%d\r\n", rc);
        while(1);
    }
}

static void sensor_event_cb(const inv_sensor_event_t * event, void * arg){
    (void)arg;
    float rx = 0.0;
    float ry = 0.0;
    float rz = 0.0;

    if(event->status == INV_SENSOR_STATUS_DATA_UPDATED){
        switch(INV_SENSOR_ID_TO_TYPE(event->sensor)){
        case INV_SENSOR_TYPE_ROTATION_VECTOR:
            q[0] = event->data.quaternion.quat[0];
            q[1] = event->data.quaternion.quat[1];
            q[2] = event->data.quaternion.quat[2];
            q[3] = event->data.quaternion.quat[3];
            aQ = event->data.quaternion.accuracy;
        case INV_SENSOR_TYPE_ACCELEROMETER:
            aA = event->data.acc.accuracy_flag;
            if(aA == 3){
                a[0] = event->data.acc.vect[0];
                a[1] = event->data.acc.vect[1];
                a[2] = event->data.acc.vect[2];
            }
//        case INV_SENSOR_TYPE_GYROSCOPE:
//            aG = event->data.gyr.accuracy_flag;
//            if(aG == 3){
//                g[0] = event->data.gyr.vect[0];
//                g[1] = event->data.gyr.vect[1];
//                g[2] = event->data.gyr.vect[2];
//            }
        case INV_SENSOR_TYPE_MAGNETOMETER:
            aM = event->data.mag.accuracy_flag;
            if(aM == 3){
                m[0] = event->data.mag.vect[0];
                m[1] = event->data.mag.vect[1];
                m[2] = event->data.mag.vect[2];
            }
            break;
        }

        rx = pow(q[0],2)+pow(q[1],2)-pow(q[2],2)-pow(q[3],2);
        ry = 2*((q[0]*q[3])+(q[1]*q[2]));
        rz = 2*((q[1]*q[3])-(q[0]*q[2]));

        theta = atan2(sqrt(pow(rx,2)+pow(ry,2)),rz);
        phi = atan2(ry,rx);

        thetaRel = theta - thetaZero;
        phiRel = phi - phiZero;

        if(thetaRel <= 0)
            angToDAC[THETA_IDX] = DAC_MAX;
        else if(thetaRel >= M_PI)
            angToDAC[THETA_IDX] = 0;
        else
            angToDAC[THETA_IDX] = (M_PI-thetaRel)*DAC_MAX*M_1_PI;

        if(phiRel <= -M_PI)
            angToDAC[PHI_IDX] = 0;
        else if(phiRel >= M_PI)
            angToDAC[PHI_IDX] = DAC_MAX;
        else
            angToDAC[PHI_IDX] = (phiRel+(M_PI))*0.5*M_1_PI*DAC_MAX;

        angToLCD[THETA_IDX] = thetaRel*180*M_1_PI;
        angToLCD[PHI_IDX] = phiRel*180*M_1_PI;
    }
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
