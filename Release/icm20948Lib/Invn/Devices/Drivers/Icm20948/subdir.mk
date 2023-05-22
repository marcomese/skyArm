################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../icm20948Lib/Invn/Devices/Drivers/Icm20948/Icm20948Augmented.c \
../icm20948Lib/Invn/Devices/Drivers/Icm20948/Icm20948AuxCompassAkm.c \
../icm20948Lib/Invn/Devices/Drivers/Icm20948/Icm20948AuxTransport.c \
../icm20948Lib/Invn/Devices/Drivers/Icm20948/Icm20948DataBaseControl.c \
../icm20948Lib/Invn/Devices/Drivers/Icm20948/Icm20948DataBaseDriver.c \
../icm20948Lib/Invn/Devices/Drivers/Icm20948/Icm20948DataConverter.c \
../icm20948Lib/Invn/Devices/Drivers/Icm20948/Icm20948Dmp3Driver.c \
../icm20948Lib/Invn/Devices/Drivers/Icm20948/Icm20948LoadFirmware.c \
../icm20948Lib/Invn/Devices/Drivers/Icm20948/Icm20948MPUFifoControl.c \
../icm20948Lib/Invn/Devices/Drivers/Icm20948/Icm20948SelfTest.c \
../icm20948Lib/Invn/Devices/Drivers/Icm20948/Icm20948Setup.c \
../icm20948Lib/Invn/Devices/Drivers/Icm20948/Icm20948Transport.c 

OBJS += \
./icm20948Lib/Invn/Devices/Drivers/Icm20948/Icm20948Augmented.o \
./icm20948Lib/Invn/Devices/Drivers/Icm20948/Icm20948AuxCompassAkm.o \
./icm20948Lib/Invn/Devices/Drivers/Icm20948/Icm20948AuxTransport.o \
./icm20948Lib/Invn/Devices/Drivers/Icm20948/Icm20948DataBaseControl.o \
./icm20948Lib/Invn/Devices/Drivers/Icm20948/Icm20948DataBaseDriver.o \
./icm20948Lib/Invn/Devices/Drivers/Icm20948/Icm20948DataConverter.o \
./icm20948Lib/Invn/Devices/Drivers/Icm20948/Icm20948Dmp3Driver.o \
./icm20948Lib/Invn/Devices/Drivers/Icm20948/Icm20948LoadFirmware.o \
./icm20948Lib/Invn/Devices/Drivers/Icm20948/Icm20948MPUFifoControl.o \
./icm20948Lib/Invn/Devices/Drivers/Icm20948/Icm20948SelfTest.o \
./icm20948Lib/Invn/Devices/Drivers/Icm20948/Icm20948Setup.o \
./icm20948Lib/Invn/Devices/Drivers/Icm20948/Icm20948Transport.o 

C_DEPS += \
./icm20948Lib/Invn/Devices/Drivers/Icm20948/Icm20948Augmented.d \
./icm20948Lib/Invn/Devices/Drivers/Icm20948/Icm20948AuxCompassAkm.d \
./icm20948Lib/Invn/Devices/Drivers/Icm20948/Icm20948AuxTransport.d \
./icm20948Lib/Invn/Devices/Drivers/Icm20948/Icm20948DataBaseControl.d \
./icm20948Lib/Invn/Devices/Drivers/Icm20948/Icm20948DataBaseDriver.d \
./icm20948Lib/Invn/Devices/Drivers/Icm20948/Icm20948DataConverter.d \
./icm20948Lib/Invn/Devices/Drivers/Icm20948/Icm20948Dmp3Driver.d \
./icm20948Lib/Invn/Devices/Drivers/Icm20948/Icm20948LoadFirmware.d \
./icm20948Lib/Invn/Devices/Drivers/Icm20948/Icm20948MPUFifoControl.d \
./icm20948Lib/Invn/Devices/Drivers/Icm20948/Icm20948SelfTest.d \
./icm20948Lib/Invn/Devices/Drivers/Icm20948/Icm20948Setup.d \
./icm20948Lib/Invn/Devices/Drivers/Icm20948/Icm20948Transport.d 


# Each subdirectory must supply rules for building sources it contributes
icm20948Lib/Invn/Devices/Drivers/Icm20948/%.o icm20948Lib/Invn/Devices/Drivers/Icm20948/%.su icm20948Lib/Invn/Devices/Drivers/Icm20948/%.cyclo: ../icm20948Lib/Invn/Devices/Drivers/Icm20948/%.c icm20948Lib/Invn/Devices/Drivers/Icm20948/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -DUSE_HAL_DRIVER -DINV_MSG_ENABLE -DSTM32L432xx -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I../FATFS/Target -I../FATFS/App -I../Middlewares/Third_Party/FatFs/src -I"C:/Users/mames/Documents/progetti_stm32/skyArm_v2/icm20948Lib" -I"C:/Users/mames/Documents/progetti_stm32/skyArm_v2/ili9341" -I"C:/Users/mames/Documents/progetti_stm32/skyArm_v2/graphics" -I"C:/Users/mames/Documents/progetti_stm32/skyArm_v2/utilLib/Inc" -I"C:/Users/mames/Documents/progetti_stm32/skyArm_v2/vl53l1x/platform" -I"C:/Users/mames/Documents/progetti_stm32/skyArm_v2/vl53l1x/core" -O3 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-icm20948Lib-2f-Invn-2f-Devices-2f-Drivers-2f-Icm20948

clean-icm20948Lib-2f-Invn-2f-Devices-2f-Drivers-2f-Icm20948:
	-$(RM) ./icm20948Lib/Invn/Devices/Drivers/Icm20948/Icm20948Augmented.cyclo ./icm20948Lib/Invn/Devices/Drivers/Icm20948/Icm20948Augmented.d ./icm20948Lib/Invn/Devices/Drivers/Icm20948/Icm20948Augmented.o ./icm20948Lib/Invn/Devices/Drivers/Icm20948/Icm20948Augmented.su ./icm20948Lib/Invn/Devices/Drivers/Icm20948/Icm20948AuxCompassAkm.cyclo ./icm20948Lib/Invn/Devices/Drivers/Icm20948/Icm20948AuxCompassAkm.d ./icm20948Lib/Invn/Devices/Drivers/Icm20948/Icm20948AuxCompassAkm.o ./icm20948Lib/Invn/Devices/Drivers/Icm20948/Icm20948AuxCompassAkm.su ./icm20948Lib/Invn/Devices/Drivers/Icm20948/Icm20948AuxTransport.cyclo ./icm20948Lib/Invn/Devices/Drivers/Icm20948/Icm20948AuxTransport.d ./icm20948Lib/Invn/Devices/Drivers/Icm20948/Icm20948AuxTransport.o ./icm20948Lib/Invn/Devices/Drivers/Icm20948/Icm20948AuxTransport.su ./icm20948Lib/Invn/Devices/Drivers/Icm20948/Icm20948DataBaseControl.cyclo ./icm20948Lib/Invn/Devices/Drivers/Icm20948/Icm20948DataBaseControl.d ./icm20948Lib/Invn/Devices/Drivers/Icm20948/Icm20948DataBaseControl.o ./icm20948Lib/Invn/Devices/Drivers/Icm20948/Icm20948DataBaseControl.su ./icm20948Lib/Invn/Devices/Drivers/Icm20948/Icm20948DataBaseDriver.cyclo ./icm20948Lib/Invn/Devices/Drivers/Icm20948/Icm20948DataBaseDriver.d ./icm20948Lib/Invn/Devices/Drivers/Icm20948/Icm20948DataBaseDriver.o ./icm20948Lib/Invn/Devices/Drivers/Icm20948/Icm20948DataBaseDriver.su ./icm20948Lib/Invn/Devices/Drivers/Icm20948/Icm20948DataConverter.cyclo ./icm20948Lib/Invn/Devices/Drivers/Icm20948/Icm20948DataConverter.d ./icm20948Lib/Invn/Devices/Drivers/Icm20948/Icm20948DataConverter.o ./icm20948Lib/Invn/Devices/Drivers/Icm20948/Icm20948DataConverter.su ./icm20948Lib/Invn/Devices/Drivers/Icm20948/Icm20948Dmp3Driver.cyclo ./icm20948Lib/Invn/Devices/Drivers/Icm20948/Icm20948Dmp3Driver.d ./icm20948Lib/Invn/Devices/Drivers/Icm20948/Icm20948Dmp3Driver.o ./icm20948Lib/Invn/Devices/Drivers/Icm20948/Icm20948Dmp3Driver.su ./icm20948Lib/Invn/Devices/Drivers/Icm20948/Icm20948LoadFirmware.cyclo ./icm20948Lib/Invn/Devices/Drivers/Icm20948/Icm20948LoadFirmware.d ./icm20948Lib/Invn/Devices/Drivers/Icm20948/Icm20948LoadFirmware.o ./icm20948Lib/Invn/Devices/Drivers/Icm20948/Icm20948LoadFirmware.su ./icm20948Lib/Invn/Devices/Drivers/Icm20948/Icm20948MPUFifoControl.cyclo ./icm20948Lib/Invn/Devices/Drivers/Icm20948/Icm20948MPUFifoControl.d ./icm20948Lib/Invn/Devices/Drivers/Icm20948/Icm20948MPUFifoControl.o ./icm20948Lib/Invn/Devices/Drivers/Icm20948/Icm20948MPUFifoControl.su ./icm20948Lib/Invn/Devices/Drivers/Icm20948/Icm20948SelfTest.cyclo ./icm20948Lib/Invn/Devices/Drivers/Icm20948/Icm20948SelfTest.d ./icm20948Lib/Invn/Devices/Drivers/Icm20948/Icm20948SelfTest.o ./icm20948Lib/Invn/Devices/Drivers/Icm20948/Icm20948SelfTest.su ./icm20948Lib/Invn/Devices/Drivers/Icm20948/Icm20948Setup.cyclo ./icm20948Lib/Invn/Devices/Drivers/Icm20948/Icm20948Setup.d ./icm20948Lib/Invn/Devices/Drivers/Icm20948/Icm20948Setup.o ./icm20948Lib/Invn/Devices/Drivers/Icm20948/Icm20948Setup.su ./icm20948Lib/Invn/Devices/Drivers/Icm20948/Icm20948Transport.cyclo ./icm20948Lib/Invn/Devices/Drivers/Icm20948/Icm20948Transport.d ./icm20948Lib/Invn/Devices/Drivers/Icm20948/Icm20948Transport.o ./icm20948Lib/Invn/Devices/Drivers/Icm20948/Icm20948Transport.su

.PHONY: clean-icm20948Lib-2f-Invn-2f-Devices-2f-Drivers-2f-Icm20948

