################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../icm20948Lib/Invn/EmbUtils/DataConverter.c \
../icm20948Lib/Invn/EmbUtils/Message.c 

OBJS += \
./icm20948Lib/Invn/EmbUtils/DataConverter.o \
./icm20948Lib/Invn/EmbUtils/Message.o 

C_DEPS += \
./icm20948Lib/Invn/EmbUtils/DataConverter.d \
./icm20948Lib/Invn/EmbUtils/Message.d 


# Each subdirectory must supply rules for building sources it contributes
icm20948Lib/Invn/EmbUtils/%.o icm20948Lib/Invn/EmbUtils/%.su: ../icm20948Lib/Invn/EmbUtils/%.c icm20948Lib/Invn/EmbUtils/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L432xx -DINV_MSG_ENABLE -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/mames/Documents/progetti_stm32/skyArm/icm20948Lib" -I"C:/Users/mames/Documents/progetti_stm32/skyArm/utilLib/Inc" -I"C:/Users/mames/Documents/progetti_stm32/skyArm/vl53l1x/core" -I"C:/Users/mames/Documents/progetti_stm32/skyArm/vl53l1x/platform" -I"C:/Users/mames/Documents/progetti_stm32/skyArm/sh1106" -I"C:/Users/mames/Documents/progetti_stm32/skyArm/bitmaps" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@"  -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-icm20948Lib-2f-Invn-2f-EmbUtils

clean-icm20948Lib-2f-Invn-2f-EmbUtils:
	-$(RM) ./icm20948Lib/Invn/EmbUtils/DataConverter.d ./icm20948Lib/Invn/EmbUtils/DataConverter.o ./icm20948Lib/Invn/EmbUtils/DataConverter.su ./icm20948Lib/Invn/EmbUtils/Message.d ./icm20948Lib/Invn/EmbUtils/Message.o ./icm20948Lib/Invn/EmbUtils/Message.su

.PHONY: clean-icm20948Lib-2f-Invn-2f-EmbUtils

