################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../vl53l5cx/Src/platform.c \
../vl53l5cx/Src/vl53l5cx_api.c \
../vl53l5cx/Src/vl53l5cx_plugin_detection_thresholds.c \
../vl53l5cx/Src/vl53l5cx_plugin_motion_indicator.c \
../vl53l5cx/Src/vl53l5cx_plugin_xtalk.c 

OBJS += \
./vl53l5cx/Src/platform.o \
./vl53l5cx/Src/vl53l5cx_api.o \
./vl53l5cx/Src/vl53l5cx_plugin_detection_thresholds.o \
./vl53l5cx/Src/vl53l5cx_plugin_motion_indicator.o \
./vl53l5cx/Src/vl53l5cx_plugin_xtalk.o 

C_DEPS += \
./vl53l5cx/Src/platform.d \
./vl53l5cx/Src/vl53l5cx_api.d \
./vl53l5cx/Src/vl53l5cx_plugin_detection_thresholds.d \
./vl53l5cx/Src/vl53l5cx_plugin_motion_indicator.d \
./vl53l5cx/Src/vl53l5cx_plugin_xtalk.d 


# Each subdirectory must supply rules for building sources it contributes
vl53l5cx/Src/platform.o: C:/Users/mames/Documents/progetti_stm32/skyArm/vl53l5cx/Src/platform.c vl53l5cx/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L432xx -DINV_MSG_ENABLE -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/mames/Documents/progetti_stm32/skyArm/icm20948Lib" -I"C:/Users/mames/Documents/progetti_stm32/skyArm/utilLib/Inc" -I../FATFS/Target -I../FATFS/App -I../Middlewares/Third_Party/FatFs/src -I"C:/Users/mames/Documents/progetti_stm32/skyArm/vl53l5cx/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@"  -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
vl53l5cx/Src/vl53l5cx_api.o: C:/Users/mames/Documents/progetti_stm32/skyArm/vl53l5cx/Src/vl53l5cx_api.c vl53l5cx/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L432xx -DINV_MSG_ENABLE -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/mames/Documents/progetti_stm32/skyArm/icm20948Lib" -I"C:/Users/mames/Documents/progetti_stm32/skyArm/utilLib/Inc" -I../FATFS/Target -I../FATFS/App -I../Middlewares/Third_Party/FatFs/src -I"C:/Users/mames/Documents/progetti_stm32/skyArm/vl53l5cx/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@"  -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
vl53l5cx/Src/vl53l5cx_plugin_detection_thresholds.o: C:/Users/mames/Documents/progetti_stm32/skyArm/vl53l5cx/Src/vl53l5cx_plugin_detection_thresholds.c vl53l5cx/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L432xx -DINV_MSG_ENABLE -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/mames/Documents/progetti_stm32/skyArm/icm20948Lib" -I"C:/Users/mames/Documents/progetti_stm32/skyArm/utilLib/Inc" -I../FATFS/Target -I../FATFS/App -I../Middlewares/Third_Party/FatFs/src -I"C:/Users/mames/Documents/progetti_stm32/skyArm/vl53l5cx/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@"  -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
vl53l5cx/Src/vl53l5cx_plugin_motion_indicator.o: C:/Users/mames/Documents/progetti_stm32/skyArm/vl53l5cx/Src/vl53l5cx_plugin_motion_indicator.c vl53l5cx/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L432xx -DINV_MSG_ENABLE -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/mames/Documents/progetti_stm32/skyArm/icm20948Lib" -I"C:/Users/mames/Documents/progetti_stm32/skyArm/utilLib/Inc" -I../FATFS/Target -I../FATFS/App -I../Middlewares/Third_Party/FatFs/src -I"C:/Users/mames/Documents/progetti_stm32/skyArm/vl53l5cx/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@"  -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
vl53l5cx/Src/vl53l5cx_plugin_xtalk.o: C:/Users/mames/Documents/progetti_stm32/skyArm/vl53l5cx/Src/vl53l5cx_plugin_xtalk.c vl53l5cx/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L432xx -DINV_MSG_ENABLE -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/mames/Documents/progetti_stm32/skyArm/icm20948Lib" -I"C:/Users/mames/Documents/progetti_stm32/skyArm/utilLib/Inc" -I../FATFS/Target -I../FATFS/App -I../Middlewares/Third_Party/FatFs/src -I"C:/Users/mames/Documents/progetti_stm32/skyArm/vl53l5cx/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@"  -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-vl53l5cx-2f-Src

clean-vl53l5cx-2f-Src:
	-$(RM) ./vl53l5cx/Src/platform.d ./vl53l5cx/Src/platform.o ./vl53l5cx/Src/platform.su ./vl53l5cx/Src/vl53l5cx_api.d ./vl53l5cx/Src/vl53l5cx_api.o ./vl53l5cx/Src/vl53l5cx_api.su ./vl53l5cx/Src/vl53l5cx_plugin_detection_thresholds.d ./vl53l5cx/Src/vl53l5cx_plugin_detection_thresholds.o ./vl53l5cx/Src/vl53l5cx_plugin_detection_thresholds.su ./vl53l5cx/Src/vl53l5cx_plugin_motion_indicator.d ./vl53l5cx/Src/vl53l5cx_plugin_motion_indicator.o ./vl53l5cx/Src/vl53l5cx_plugin_motion_indicator.su ./vl53l5cx/Src/vl53l5cx_plugin_xtalk.d ./vl53l5cx/Src/vl53l5cx_plugin_xtalk.o ./vl53l5cx/Src/vl53l5cx_plugin_xtalk.su

.PHONY: clean-vl53l5cx-2f-Src

