################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../vl53l1x/platform/vl53l1_platform.c 

OBJS += \
./vl53l1x/platform/vl53l1_platform.o 

C_DEPS += \
./vl53l1x/platform/vl53l1_platform.d 


# Each subdirectory must supply rules for building sources it contributes
vl53l1x/platform/vl53l1_platform.o: C:/Users/mames/Documents/progetti_stm32/skyArm_v2/vl53l1x/platform/vl53l1_platform.c vl53l1x/platform/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L432xx -DINV_MSG_ENABLE -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I../FATFS/Target -I../FATFS/App -I../Middlewares/Third_Party/FatFs/src -I"C:/Users/mames/Documents/progetti_stm32/skyArm_v2/ili9341" -I"C:/Users/mames/Documents/progetti_stm32/skyArm_v2/graphics" -I"C:/Users/mames/Documents/progetti_stm32/skyArm_v2/vl53l1x/core" -I"C:/Users/mames/Documents/progetti_stm32/skyArm_v2/vl53l1x/platform" -I"C:/Users/mames/Documents/progetti_stm32/skyArm_v2/icm20948Lib" -I"C:/Users/mames/Documents/progetti_stm32/skyArm_v2/utilLib/Inc" -O3 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@"  -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-vl53l1x-2f-platform

clean-vl53l1x-2f-platform:
	-$(RM) ./vl53l1x/platform/vl53l1_platform.d ./vl53l1x/platform/vl53l1_platform.o ./vl53l1x/platform/vl53l1_platform.su

.PHONY: clean-vl53l1x-2f-platform

