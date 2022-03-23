################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../bitmaps/configScreen.c \
../bitmaps/homeScreen.c \
../bitmaps/infoScreen.c 

OBJS += \
./bitmaps/configScreen.o \
./bitmaps/homeScreen.o \
./bitmaps/infoScreen.o 

C_DEPS += \
./bitmaps/configScreen.d \
./bitmaps/homeScreen.d \
./bitmaps/infoScreen.d 


# Each subdirectory must supply rules for building sources it contributes
bitmaps/configScreen.o: C:/Users/mames/Documents/progetti_stm32/skyArm/bitmaps/configScreen.c bitmaps/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L432xx -DINV_MSG_ENABLE -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/mames/Documents/progetti_stm32/skyArm/icm20948Lib" -I"C:/Users/mames/Documents/progetti_stm32/skyArm/utilLib/Inc" -I"C:/Users/mames/Documents/progetti_stm32/skyArm/vl53l1x/core" -I"C:/Users/mames/Documents/progetti_stm32/skyArm/vl53l1x/platform" -I"C:/Users/mames/Documents/progetti_stm32/skyArm/sh1106" -I"C:/Users/mames/Documents/progetti_stm32/skyArm/bitmaps" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@"  -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
bitmaps/homeScreen.o: C:/Users/mames/Documents/progetti_stm32/skyArm/bitmaps/homeScreen.c bitmaps/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L432xx -DINV_MSG_ENABLE -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/mames/Documents/progetti_stm32/skyArm/icm20948Lib" -I"C:/Users/mames/Documents/progetti_stm32/skyArm/utilLib/Inc" -I"C:/Users/mames/Documents/progetti_stm32/skyArm/vl53l1x/core" -I"C:/Users/mames/Documents/progetti_stm32/skyArm/vl53l1x/platform" -I"C:/Users/mames/Documents/progetti_stm32/skyArm/sh1106" -I"C:/Users/mames/Documents/progetti_stm32/skyArm/bitmaps" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@"  -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
bitmaps/infoScreen.o: C:/Users/mames/Documents/progetti_stm32/skyArm/bitmaps/infoScreen.c bitmaps/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L432xx -DINV_MSG_ENABLE -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/mames/Documents/progetti_stm32/skyArm/icm20948Lib" -I"C:/Users/mames/Documents/progetti_stm32/skyArm/utilLib/Inc" -I"C:/Users/mames/Documents/progetti_stm32/skyArm/vl53l1x/core" -I"C:/Users/mames/Documents/progetti_stm32/skyArm/vl53l1x/platform" -I"C:/Users/mames/Documents/progetti_stm32/skyArm/sh1106" -I"C:/Users/mames/Documents/progetti_stm32/skyArm/bitmaps" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@"  -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-bitmaps

clean-bitmaps:
	-$(RM) ./bitmaps/configScreen.d ./bitmaps/configScreen.o ./bitmaps/configScreen.su ./bitmaps/homeScreen.d ./bitmaps/homeScreen.o ./bitmaps/homeScreen.su ./bitmaps/infoScreen.d ./bitmaps/infoScreen.o ./bitmaps/infoScreen.su

.PHONY: clean-bitmaps

