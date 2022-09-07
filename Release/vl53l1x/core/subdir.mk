################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../vl53l1x/core/VL53L1X_api.c \
../vl53l1x/core/VL53L1X_calibration.c 

OBJS += \
./vl53l1x/core/VL53L1X_api.o \
./vl53l1x/core/VL53L1X_calibration.o 

C_DEPS += \
./vl53l1x/core/VL53L1X_api.d \
./vl53l1x/core/VL53L1X_calibration.d 


# Each subdirectory must supply rules for building sources it contributes
vl53l1x/core/VL53L1X_api.o: C:/Users/mames/Documents/progetti_stm32/skyArm_v2/vl53l1x/core/VL53L1X_api.c vl53l1x/core/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -DUSE_HAL_DRIVER -DINV_MSG_ENABLE -DSTM32L432xx -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I../FATFS/Target -I../FATFS/App -I../Middlewares/Third_Party/FatFs/src -I"C:/Users/mames/Documents/progetti_stm32/skyArm_v2/icm20948Lib" -I"C:/Users/mames/Documents/progetti_stm32/skyArm_v2/ili9341" -I"C:/Users/mames/Documents/progetti_stm32/skyArm_v2/graphics" -I"C:/Users/mames/Documents/progetti_stm32/skyArm_v2/utilLib/Inc" -I"C:/Users/mames/Documents/progetti_stm32/skyArm_v2/vl53l1x/platform" -I"C:/Users/mames/Documents/progetti_stm32/skyArm_v2/vl53l1x/core" -O3 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
vl53l1x/core/VL53L1X_calibration.o: C:/Users/mames/Documents/progetti_stm32/skyArm_v2/vl53l1x/core/VL53L1X_calibration.c vl53l1x/core/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -DUSE_HAL_DRIVER -DINV_MSG_ENABLE -DSTM32L432xx -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I../FATFS/Target -I../FATFS/App -I../Middlewares/Third_Party/FatFs/src -I"C:/Users/mames/Documents/progetti_stm32/skyArm_v2/icm20948Lib" -I"C:/Users/mames/Documents/progetti_stm32/skyArm_v2/ili9341" -I"C:/Users/mames/Documents/progetti_stm32/skyArm_v2/graphics" -I"C:/Users/mames/Documents/progetti_stm32/skyArm_v2/utilLib/Inc" -I"C:/Users/mames/Documents/progetti_stm32/skyArm_v2/vl53l1x/platform" -I"C:/Users/mames/Documents/progetti_stm32/skyArm_v2/vl53l1x/core" -O3 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-vl53l1x-2f-core

clean-vl53l1x-2f-core:
	-$(RM) ./vl53l1x/core/VL53L1X_api.d ./vl53l1x/core/VL53L1X_api.o ./vl53l1x/core/VL53L1X_api.su ./vl53l1x/core/VL53L1X_calibration.d ./vl53l1x/core/VL53L1X_calibration.o ./vl53l1x/core/VL53L1X_calibration.su

.PHONY: clean-vl53l1x-2f-core

