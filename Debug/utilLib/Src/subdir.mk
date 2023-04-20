################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../utilLib/Src/I2CSerifHal.c \
../utilLib/Src/filesLib.c \
../utilLib/Src/timerDelay.c 

OBJS += \
./utilLib/Src/I2CSerifHal.o \
./utilLib/Src/filesLib.o \
./utilLib/Src/timerDelay.o 

C_DEPS += \
./utilLib/Src/I2CSerifHal.d \
./utilLib/Src/filesLib.d \
./utilLib/Src/timerDelay.d 


# Each subdirectory must supply rules for building sources it contributes
utilLib/Src/%.o utilLib/Src/%.su utilLib/Src/%.cyclo: ../utilLib/Src/%.c utilLib/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L432xx -DINV_MSG_ENABLE -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I../FATFS/Target -I../FATFS/App -I../Middlewares/Third_Party/FatFs/src -I"C:/Users/mames/Documents/progetti_stm32/skyArm_v2/ili9341" -I"C:/Users/mames/Documents/progetti_stm32/skyArm_v2/graphics" -I"C:/Users/mames/Documents/progetti_stm32/skyArm_v2/vl53l1x/core" -I"C:/Users/mames/Documents/progetti_stm32/skyArm_v2/vl53l1x/platform" -I"C:/Users/mames/Documents/progetti_stm32/skyArm_v2/icm20948Lib" -I"C:/Users/mames/Documents/progetti_stm32/skyArm_v2/utilLib/Inc" -O3 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@"  -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-utilLib-2f-Src

clean-utilLib-2f-Src:
	-$(RM) ./utilLib/Src/I2CSerifHal.cyclo ./utilLib/Src/I2CSerifHal.d ./utilLib/Src/I2CSerifHal.o ./utilLib/Src/I2CSerifHal.su ./utilLib/Src/filesLib.cyclo ./utilLib/Src/filesLib.d ./utilLib/Src/filesLib.o ./utilLib/Src/filesLib.su ./utilLib/Src/timerDelay.cyclo ./utilLib/Src/timerDelay.d ./utilLib/Src/timerDelay.o ./utilLib/Src/timerDelay.su

.PHONY: clean-utilLib-2f-Src

