################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../graphics/display.c \
../graphics/screen.c \
../graphics/tiles.c \
../graphics/tilesFunctions.c 

OBJS += \
./graphics/display.o \
./graphics/screen.o \
./graphics/tiles.o \
./graphics/tilesFunctions.o 

C_DEPS += \
./graphics/display.d \
./graphics/screen.d \
./graphics/tiles.d \
./graphics/tilesFunctions.d 


# Each subdirectory must supply rules for building sources it contributes
graphics/display.o: C:/Users/mames/Documents/progetti_stm32/skyArm_v2/graphics/display.c graphics/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -DUSE_HAL_DRIVER -DINV_MSG_ENABLE -DSTM32L432xx -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I../FATFS/Target -I../FATFS/App -I../Middlewares/Third_Party/FatFs/src -I"C:/Users/mames/Documents/progetti_stm32/skyArm_v2/icm20948Lib" -I"C:/Users/mames/Documents/progetti_stm32/skyArm_v2/ili9341" -I"C:/Users/mames/Documents/progetti_stm32/skyArm_v2/graphics" -I"C:/Users/mames/Documents/progetti_stm32/skyArm_v2/utilLib/Inc" -I"C:/Users/mames/Documents/progetti_stm32/skyArm_v2/vl53l1x/platform" -I"C:/Users/mames/Documents/progetti_stm32/skyArm_v2/vl53l1x/core" -O3 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
graphics/screen.o: C:/Users/mames/Documents/progetti_stm32/skyArm_v2/graphics/screen.c graphics/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -DUSE_HAL_DRIVER -DINV_MSG_ENABLE -DSTM32L432xx -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I../FATFS/Target -I../FATFS/App -I../Middlewares/Third_Party/FatFs/src -I"C:/Users/mames/Documents/progetti_stm32/skyArm_v2/icm20948Lib" -I"C:/Users/mames/Documents/progetti_stm32/skyArm_v2/ili9341" -I"C:/Users/mames/Documents/progetti_stm32/skyArm_v2/graphics" -I"C:/Users/mames/Documents/progetti_stm32/skyArm_v2/utilLib/Inc" -I"C:/Users/mames/Documents/progetti_stm32/skyArm_v2/vl53l1x/platform" -I"C:/Users/mames/Documents/progetti_stm32/skyArm_v2/vl53l1x/core" -O3 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
graphics/tiles.o: C:/Users/mames/Documents/progetti_stm32/skyArm_v2/graphics/tiles.c graphics/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -DUSE_HAL_DRIVER -DINV_MSG_ENABLE -DSTM32L432xx -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I../FATFS/Target -I../FATFS/App -I../Middlewares/Third_Party/FatFs/src -I"C:/Users/mames/Documents/progetti_stm32/skyArm_v2/icm20948Lib" -I"C:/Users/mames/Documents/progetti_stm32/skyArm_v2/ili9341" -I"C:/Users/mames/Documents/progetti_stm32/skyArm_v2/graphics" -I"C:/Users/mames/Documents/progetti_stm32/skyArm_v2/utilLib/Inc" -I"C:/Users/mames/Documents/progetti_stm32/skyArm_v2/vl53l1x/platform" -I"C:/Users/mames/Documents/progetti_stm32/skyArm_v2/vl53l1x/core" -O3 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
graphics/tilesFunctions.o: C:/Users/mames/Documents/progetti_stm32/skyArm_v2/graphics/tilesFunctions.c graphics/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -DUSE_HAL_DRIVER -DINV_MSG_ENABLE -DSTM32L432xx -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I../FATFS/Target -I../FATFS/App -I../Middlewares/Third_Party/FatFs/src -I"C:/Users/mames/Documents/progetti_stm32/skyArm_v2/icm20948Lib" -I"C:/Users/mames/Documents/progetti_stm32/skyArm_v2/ili9341" -I"C:/Users/mames/Documents/progetti_stm32/skyArm_v2/graphics" -I"C:/Users/mames/Documents/progetti_stm32/skyArm_v2/utilLib/Inc" -I"C:/Users/mames/Documents/progetti_stm32/skyArm_v2/vl53l1x/platform" -I"C:/Users/mames/Documents/progetti_stm32/skyArm_v2/vl53l1x/core" -O3 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-graphics

clean-graphics:
	-$(RM) ./graphics/display.d ./graphics/display.o ./graphics/display.su ./graphics/screen.d ./graphics/screen.o ./graphics/screen.su ./graphics/tiles.d ./graphics/tiles.o ./graphics/tiles.su ./graphics/tilesFunctions.d ./graphics/tilesFunctions.o ./graphics/tilesFunctions.su

.PHONY: clean-graphics

