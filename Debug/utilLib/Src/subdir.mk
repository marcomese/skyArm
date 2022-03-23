################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../utilLib/Src/I2CSerifHal.c \
../utilLib/Src/custom_fonts.c \
../utilLib/Src/retarget.c \
../utilLib/Src/timerDelay.c 

OBJS += \
./utilLib/Src/I2CSerifHal.o \
./utilLib/Src/custom_fonts.o \
./utilLib/Src/retarget.o \
./utilLib/Src/timerDelay.o 

C_DEPS += \
./utilLib/Src/I2CSerifHal.d \
./utilLib/Src/custom_fonts.d \
./utilLib/Src/retarget.d \
./utilLib/Src/timerDelay.d 


# Each subdirectory must supply rules for building sources it contributes
utilLib/Src/%.o utilLib/Src/%.su: ../utilLib/Src/%.c utilLib/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L432xx -DINV_MSG_ENABLE -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/mames/Documents/progetti_stm32/skyArm/icm20948Lib" -I"C:/Users/mames/Documents/progetti_stm32/skyArm/utilLib/Inc" -I"C:/Users/mames/Documents/progetti_stm32/skyArm/vl53l1x/core" -I"C:/Users/mames/Documents/progetti_stm32/skyArm/vl53l1x/platform" -I"C:/Users/mames/Documents/progetti_stm32/skyArm/sh1106" -I"C:/Users/mames/Documents/progetti_stm32/skyArm/bitmaps" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@"  -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-utilLib-2f-Src

clean-utilLib-2f-Src:
	-$(RM) ./utilLib/Src/I2CSerifHal.d ./utilLib/Src/I2CSerifHal.o ./utilLib/Src/I2CSerifHal.su ./utilLib/Src/custom_fonts.d ./utilLib/Src/custom_fonts.o ./utilLib/Src/custom_fonts.su ./utilLib/Src/retarget.d ./utilLib/Src/retarget.o ./utilLib/Src/retarget.su ./utilLib/Src/timerDelay.d ./utilLib/Src/timerDelay.o ./utilLib/Src/timerDelay.su

.PHONY: clean-utilLib-2f-Src

