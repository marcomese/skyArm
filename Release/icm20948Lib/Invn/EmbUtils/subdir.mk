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
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -DUSE_HAL_DRIVER -DINV_MSG_ENABLE -DSTM32L432xx -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I../FATFS/Target -I../FATFS/App -I../Middlewares/Third_Party/FatFs/src -I"C:/Users/mames/Documents/progetti_stm32/skyArm_v2/icm20948Lib" -I"C:/Users/mames/Documents/progetti_stm32/skyArm_v2/ili9341" -I"C:/Users/mames/Documents/progetti_stm32/skyArm_v2/graphics" -I"C:/Users/mames/Documents/progetti_stm32/skyArm_v2/utilLib/Inc" -I"C:/Users/mames/Documents/progetti_stm32/skyArm_v2/vl53l1x/platform" -I"C:/Users/mames/Documents/progetti_stm32/skyArm_v2/vl53l1x/core" -O3 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-icm20948Lib-2f-Invn-2f-EmbUtils

clean-icm20948Lib-2f-Invn-2f-EmbUtils:
	-$(RM) ./icm20948Lib/Invn/EmbUtils/DataConverter.d ./icm20948Lib/Invn/EmbUtils/DataConverter.o ./icm20948Lib/Invn/EmbUtils/DataConverter.su ./icm20948Lib/Invn/EmbUtils/Message.d ./icm20948Lib/Invn/EmbUtils/Message.o ./icm20948Lib/Invn/EmbUtils/Message.su

.PHONY: clean-icm20948Lib-2f-Invn-2f-EmbUtils

