################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../icm20948Lib/Invn/Devices/DeviceIcm20948.c \
../icm20948Lib/Invn/Devices/HostSerif.c \
../icm20948Lib/Invn/Devices/Sensor.c 

OBJS += \
./icm20948Lib/Invn/Devices/DeviceIcm20948.o \
./icm20948Lib/Invn/Devices/HostSerif.o \
./icm20948Lib/Invn/Devices/Sensor.o 

C_DEPS += \
./icm20948Lib/Invn/Devices/DeviceIcm20948.d \
./icm20948Lib/Invn/Devices/HostSerif.d \
./icm20948Lib/Invn/Devices/Sensor.d 


# Each subdirectory must supply rules for building sources it contributes
icm20948Lib/Invn/Devices/%.o icm20948Lib/Invn/Devices/%.su: ../icm20948Lib/Invn/Devices/%.c icm20948Lib/Invn/Devices/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L432xx -DINV_MSG_ENABLE -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I../FATFS/Target -I../FATFS/App -I../Middlewares/Third_Party/FatFs/src -I"C:/Users/mames/Documents/progetti_stm32/skyArm_v2/ili9341" -I"C:/Users/mames/Documents/progetti_stm32/skyArm_v2/graphics" -I"C:/Users/mames/Documents/progetti_stm32/skyArm_v2/vl53l1x/core" -I"C:/Users/mames/Documents/progetti_stm32/skyArm_v2/vl53l1x/platform" -I"C:/Users/mames/Documents/progetti_stm32/skyArm_v2/icm20948Lib" -I"C:/Users/mames/Documents/progetti_stm32/skyArm_v2/utilLib/Inc" -O3 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@"  -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-icm20948Lib-2f-Invn-2f-Devices

clean-icm20948Lib-2f-Invn-2f-Devices:
	-$(RM) ./icm20948Lib/Invn/Devices/DeviceIcm20948.d ./icm20948Lib/Invn/Devices/DeviceIcm20948.o ./icm20948Lib/Invn/Devices/DeviceIcm20948.su ./icm20948Lib/Invn/Devices/HostSerif.d ./icm20948Lib/Invn/Devices/HostSerif.o ./icm20948Lib/Invn/Devices/HostSerif.su ./icm20948Lib/Invn/Devices/Sensor.d ./icm20948Lib/Invn/Devices/Sensor.o ./icm20948Lib/Invn/Devices/Sensor.su

.PHONY: clean-icm20948Lib-2f-Invn-2f-Devices

